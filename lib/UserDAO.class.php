<?php
/********************************************************************
* @name User Data Access Object
* @abstract User Data Access Object -- contains properties/methods of a
* 			user
* @since Feb 12, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/
 
require_once 'DAO.class.php';
 
class UserDAO extends DAO {

	protected $username = "";
	protected $password = "";
	protected $created_on = "";
	protected $namefirst = "";
	protected $namelast = "";
	protected $email = "";
	protected $organization = "";
	protected $numtasks;
	protected $level;
	protected $cpuHours;
	protected $emailConfirmed;
	protected $approved;
	
    public function __construct() {
    	$this->table = "users";
    }
    
    public function login() {
    	$conn =& IFoldDB::getConn();
    	//sanity checks
    	if (isset($this->username) && isset($this->password)) {
    		$rs = $conn->execute("SELECT * FROM users WHERE username = " . 
    			$conn->qstr($this->username,get_magic_quotes_gpc()) . 
				" AND password = " . $conn->qstr($this->password,get_magic_quotes_gpc()) . 
				" AND approved = 1" .
				" LIMIT 1");
    		if ($rs->RecordCount() > 0) {
    			$this->digest($rs->fields);
    			return true;
    		}
    		else
    			return false;
    	} 
    	else 
    		return false;
    }
	
    public function getUsers() {
    	$conn =& IFoldDB::getConn();
    	if ($this->level > 2) {
    		$rs = $conn->execute("SELECT * FROM users " .
    							 //"WHERE emailConfirmed = 1" .
								 "");
    		$rs->MoveFirst();
    		while (! $rs->EOF) {
    			$userDAO = new UserDAO();
    			$userDAO->digest($rs->fields);
    			$finalArray[] = $userDAO;
    			$rs->MoveNext();
    		}
    		return $finalArray;
    	} 
    	else 
    		return false;
    }	
}
?>
