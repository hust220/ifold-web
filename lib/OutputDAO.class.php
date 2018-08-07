<?php
/********************************************************************
* @name Output Data Access Object
* @abstract Contains accessors to the outputs table
* @since Feb 12, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/
 
require_once 'DAO.class.php';
 
class OutputDAO extends DAO {

	protected $task_id;
	protected $fileName = "";
	protected $outputType = "";
	
    public function __construct() {
    	$this->table = "outputs";
    }
   
}
?>