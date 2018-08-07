<?php
/********************************************************************
 * @name Task Data Access Object
 * @abstract Task Data Access Object -- contains properties/methods of a
 * 			single task
 * @since Feb 27, 2006
 * -------------------------------------------------------------------/
 *
 * @author		Jameson Lopp jameson@unc.edu
 * @author		Adi Unnithan adi@unc.edu
 *				Daniel Watson dcwatson@email.unc.edu
 *********************************************************************/

require_once 'DAO.class.php';

class TaskDAO extends DAO {

  protected $param_id;
  protected $name;
  protected $description;
  protected $created_by;
  protected $created_on;
  protected $completed_on;
  protected $status;
  protected $queuenum;
  protected $daemon_uri;

  public function __construct() {
    $this->table = "tasks";
  }

  public function add() {
    $conn =& IFoldDB::getConn();

    //make sure user isn't exceeding their allowed number of tasks
    $rs = $conn->execute("SELECT * FROM users WHERE id = " . $conn->qstr($this->created_by,get_magic_quotes_gpc()) . "LIMIT 1");
    $numTasks = $rs->fields['numtasks'];
    $currentTasks = $conn->execute("SELECT * FROM tasks WHERE created_by = " . $conn->qstr($this->created_by,get_magic_quotes_gpc()) . "AND queuenum > 0");
    if ($currentTasks->RecordCount() >= $numTasks) return false;

    $rs = $conn->execute("SELECT MAX(queuenum) FROM tasks WHERE status = 1");
    $this->queuenum = $rs->fields['MAX(queuenum)'] + 1; // make last in queue
    $rs = $conn->execute("INSERT INTO tasks (" .
        "param_id," .
        "name," . 
        "description," .
        "created_by," .
        "created_on," .
        "completed_on," .
        "queuenum)" .
        " values (" .
        $conn->qstr($this->param_id, get_magic_quotes_gpc()) . "," . 
        $conn->qstr($this->name,get_magic_quotes_gpc()) . "," .
        $conn->qstr($this->description,get_magic_quotes_gpc()) . "," .
        $conn->qstr($this->created_by,get_magic_quotes_gpc()) . "," .
        "CURRENT_TIMESTAMP," .
        $conn->qstr(0,get_magic_quotes_gpc()) . "," .
        $conn->qstr($this->queuenum,get_magic_quotes_gpc()) . ")");

    $this->set('id', $conn->Insert_ID());

    return true;

  }

  public function delete(){
    $conn =& IFoldDB::getConn();
    if(isset($this->id) && isset($this->queuenum)) // delete row from table and update other rows to push them up in the queue
    {
      $conn->execute("DELETE FROM tasks WHERE ID = " . $conn->qstr($this->id, get_magic_quotes_gpc()));
      $conn->execute("UPDATE tasks SET queuenum = queuenum-1 WHERE queuenum > " . $conn->qstr($this->queuenum, get_magic_quotes_gpc()));
      return true;
    }
    return false;
  }

  public function resetTask() {
    $conn =& IFoldDB::getConn();
    $conn->execute("UPDATE tasks SET queuenum = queuenum+1");
    $conn->execute("UPDATE tasks SET queuenum = 1, status = 1 WHERE ID = " . $conn->qstr($this->id, get_magic_quotes_gpc()));
    return true;
  }

  public function getQueue($admin = false, $filter = null, $options = "") {
    $conn =& IFoldDB::getConn();
    $filterQuery = "";
    if ($filter != null) {
      $filterArray = explode(",", $filter);
      foreach ($filterArray as $column) {
        $columnPair = explode("=", $column);
        $filterQuery .= "AND {$columnPair[0]} = " . $conn->qstr($columnPair[1], get_magic_quotes_gpc()) . " ";
      }
    }
    $query = "SELECT * FROM tasks WHERE 1=1 ";
    //sanity check
    if ($admin) {
      $query .= $filterQuery;	
    } else {
      $query .= "AND status != 5 ";	
    }
    $query .= $options;
    //print $query;
    $rs = $conn->execute($query);
    $rs->MoveFirst();
    $queue = array();
    $queueItemCount = 0;

    while (! $rs->EOF) {
      $taskDAO = new TaskDAO();
      $taskDAO->digest($rs->fields);
      $userFromTask = new UserDAO();
      $userFromTask->fetch($taskDAO->get('created_by'), "id,username,email");
      $queue[$queueItemCount]['user'] = $userFromTask;
      $queue[$queueItemCount]['task'] = $taskDAO;
      $queueItemCount++;
      $rs->MoveNext();
    }

    return $queue;
  }	

  public function getUserTasks($filter = null) {
    $conn =& IFoldDB::getConn();
    $query = 	"SELECT * FROM tasks WHERE created_by = " . 
      $conn->qstr($this->created_by,get_magic_quotes_gpc()) . " ";
    if ($filter != null) {
      $filterArray = explode(",", $filter);
      foreach ($filterArray as $column) {
        $columnPair = explode("=", $column);
        $query .= "AND {$columnPair[0]} = " . $conn->qstr($columnPair[1], get_magic_quotes_gpc()) . " ";
      }
    }
    $query .= "ORDER BY queuenum";
    $rs = $conn->execute($query);
    $rs->MoveFirst();
    $finalArray = array();
    while (! $rs->EOF) {
      $taskDAO = new TaskDAO();
      $taskDAO->digest($rs->fields);
      $finalArray[] = $taskDAO;
      $rs->MoveNext();
    }
    return $finalArray;
  }

  public function getUserOutputTasks() {
    $conn =& IFoldDB::getConn();
    $rs = $conn->execute("SELECT tasks.name, tasks.description, tasks.created_on, outputs.id, outputs.fileName, outputs.outputType " .
        "FROM tasks INNER JOIN outputs " .
        "ON outputs.task_id = tasks.id " .
        "WHERE created_by = " . $conn->qstr($this->created_by,get_magic_quotes_gpc()) . " " .
        "ORDER BY tasks.name");
    $rs->MoveFirst();
    $finalArray = array();
    while (! $rs->EOF) {
      $taskDAO = new TaskDAO();
      $taskDAO->digest($rs->fields);
      $finalArray[] = $taskDAO;
      $rs->MoveNext();
    }
    return $finalArray;
  }

  public static function resetTasks() {
    $conn =& IFoldDB::getConn();
    $rs = $conn->execute("UPDATE tasks SET status = 1 WHERE status = 8");

  }

  public static function getNumWorking() {
    $conn =& IFoldDB::getConn();
    $rs = $conn->execute("SELECT * FROM tasks WHERE status = 4 OR status = 3");
    return $rs->RecordCount();
  }

  public static function getNumWaiting() {
    $conn =& IFoldDB::getConn();
    $rs = $conn->execute("SELECT * FROM tasks WHERE status = 2 OR status = 1 OR status = 6");
    return $rs->RecordCount();
  }
}
?>
