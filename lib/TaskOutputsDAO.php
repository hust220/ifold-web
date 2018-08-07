<?php
/********************************************************************
* @name Task Outputs Data Access Object
* @abstract contains properties of outputs for a single task
* 
* @since Mar 1, 2006
* -------------------------------------------------------------------/
*
* @author		Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

require_once 'DAO.class.php';
 
class TaskOutputsDAO extends DAO {

	//output table fields
	protected $task_id;
	protected $trajectoryModelType;
	protected $trajectoryMin;
	protected $trajectoryMax;
	protected $trajectoryInterval;
	protected $contactFrequencyMap;
	protected $cvVsTemp;
	protected $equilibriumOffset;
	protected $energyVsTemp;
	protected $energyVsTime;
	protected $radiusVsTime;
		
    public function __construct() {
    	$this->table = "taskoutputs";
    }

}
?>
