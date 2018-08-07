<?php
/********************************************************************
* @name Data Access Object
* @abstract Superclass of all data access objects, contains generic
* 			CRUDS methods
* @since Feb 12, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/
 
class DAO {

	protected $table;
	protected $id;
	protected $props;

    public function __construct() { }
      
    public function set($propName, $propValue) {
    	$this->$propName = $propValue;
    	$this->props[$propName] = $propValue;
    }
    
    public function get($propName) {
   		return $this->$propName;
   	}
   	
   	/**
   	 * given an associative array, sets all member properties
   	 */
   	public function digest($rsFields) {
   		foreach ($rsFields as $name => $value) {
   			$this->props[$name] = $value;
   			$this->$name = $value;
   		}
   	}
    
    public function fetch($id, $columns = "*") {
    	$conn =& IFoldDB::getConn();
   		$rs = $conn->execute("SELECT $columns FROM " . $this->table . " where ID = " . $conn->qstr($id,get_magic_quotes_gpc()) . " LIMIT 1");
   		if (!$rs) return false;
   		else $this->digest($rs->fields);
   		return true;
    }
    
    public function fetchAll($type = 'index', $options = null, $columns = '*') {
    	$conn =& IFoldDB::getConn();
    	$query = "SELECT $columns FROM " . $this->table . " WHERE 1 = 1";
    	foreach ($options as $name => $value) {
    		$query .= " $value ($name = " . $conn->qstr($this->$name,get_magic_quotes_gpc()) . ")";
    	}
    	$rs = $conn->execute($query);
    	if (!$rs) throw new DBRecordNotFoundException();
  		if ($type == 'index') $rowArray = $rs->GetRows();
  		else if ($type == 'assoc') $rowArray = $rs->GetAssoc();
    	return $rowArray;
    }
    
    public function save() {
    	try {
    		$conn =& IFoldDB::getConn();
			if ($this->search(array('id'), array($this->id))) 
	    		return $conn->AutoExecute($this->table, $this->props, 'UPDATE', "id = '" . $this->id . "'");
			else
				return false;
    	} catch (exception $e) {
    		return false;	
    	}
    }
    
    public function add() {
    	try {
    		$conn =& IFoldDB::getConn();
    		$tester = $conn->AutoExecute($this->table, $this->props, 'INSERT');
    		$this->set('id', $conn->Insert_ID());
    		return $tester;
    	} catch (exception $e) {
    		return false;
    		//var_dump($e); 
			//adodb_backtrace($e->gettrace());
    	}
    }
    
    public function search($nameArr, $valArr) {
    	try {
    		$conn =& IFoldDB::getConn();
    		$query = "SELECT * FROM " . $this->table . " WHERE 1 ";
    		for ($i=0;$i<count($nameArr);$i++) {
    			$query .= "AND ({$nameArr[$i]} = " . 
    						$conn->qstr($valArr[$i],get_magic_quotes_gpc()) . ") ";
    		}
    		$rs = $conn->execute($query);
    		if ($rs->RecordCount() < 1) return false;
    		else return $rs->GetRows();
    	} catch (exception $e) {
    		return false;
    	}
    }
    
    public function delete() {
    	try {
    		$conn =& IFoldDB::getConn();
    		$rs = $conn->execute("DELETE FROM " . $this->table . " WHERE ID = " . $conn->qstr($this->id, get_magic_quotes_gpc()));
    		return true;
    	} catch (exception $e) {
    		return false;	
    	}
    }
    
    public function toXML() {
    	$xml = "<object>";
    	$xml .= "<table>{$this->table}</table>";
    	foreach ($this->props as $name => $value) {
    		$xml .= "<property>";
    		$xml .= "<name>$name</name>";
    		$xml .= "<value>$value</value>";
    		$xml .= "</property>";
    	}
    	$xml .= "</object>";
    	return $xml;
    }
}
?>
