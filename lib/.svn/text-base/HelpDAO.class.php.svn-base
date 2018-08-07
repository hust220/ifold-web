<?php
/********************************************************************
* @name Help Data Access Object
* @abstract allows manipulation and retrieval of help pages
* 			
* @since Mar 30, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/
 
require_once 'DAO.class.php';
 
class HelpDAO extends DAO {

	protected $name = "";
	protected $level = "";
	protected $description = "";
	protected $author = "";
	protected $content = "";
	protected $id = "";
	
    public function __construct() {
    	$this->table = "helppages";
    	$this->level = 0; // default for new pages
    }
	
    public function getHelp() {
    	$conn =& IFoldDB::getConn();
    		$rs = $conn->execute("SELECT * FROM $this->table");
    		$rs->MoveFirst();
    		while (! $rs->EOF) {
    			$help = new HelpDAO();
    			$help->digest($rs->fields);
    			$finalArray[] = $help;
    			$rs->MoveNext();
    		}
    		return $finalArray;
    }	
}
?>
