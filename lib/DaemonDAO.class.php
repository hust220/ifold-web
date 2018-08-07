<?php
/********************************************************************
* @name Task Data Access Object
* @abstract Daemon Data Access Object -- contains properties/methods of a
* 			single daemon
* @since Feb 27, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require_once 'DAO.class.php';
 
class DaemonDAO extends DAO {
	
	protected $id;
	protected $address;
	protected $port;
	protected $status;
	protected $action;
	protected $taskId;
	
	public function __construct() {
    	$this->table = "daemons";
    }
    
    public static function getAtAGlance() {
    	$conn =& IFoldDB::getConn();
    	$rs = $conn->execute("SELECT * FROM daemons");
    	$finalArray = array();
    	while (! $rs->EOF) {
			$daemonDAO = new DaemonDAO();
			$daemonDAO->digest($rs->fields);
			$finalArray[] = $daemonDAO;
   			$rs->MoveNext();
   		}
   		return $finalArray;
    }
    
    public function getDaemons() {
    	$conn =& IFoldDB::getConn();
    	$rs = $conn->execute("SELECT * FROM daemons");
		$rs->MoveFirst();
		$finalArray = array();
		while (! $rs->EOF) {
			$daemonDAO = new DaemonDAO();
			$daemonDAO->digest($rs->fields);
			$finalArray[] = $daemonDAO;
			$rs->MoveNext();
		}
		return $finalArray;
    }
    
    public static function setAllDaemons($status) {
    	$conn =& IFoldDB::getConn();
    	$rs = $conn->execute("UPDATE daemons SET status = " . $conn->qstr($status, get_magic_quotes_gpc()));
    	
    }
    
}
?>