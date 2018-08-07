<?php
/********************************************************************
* @name IFoldProps
* @abstract - Editable properties of the IFold project
* @since Feb 20, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/

class IFoldProps {
	
	private $xmlstr;

    function IFoldProps() {
    	$this->xmlstr = simplexml_load_file(PROPS_PATH);
    }
    
    private function genericGet($parent) {
    	$count = 1;
   		foreach ($this->xmlstr->$parent->children() as $item) {
    		$itemListArr[$count++] = $item;
    	}
    	return $itemListArr;
    }
    
    public function getConfig($name) {
    	$itemArr = $this->xmlstr->xpath('//configuration/config[name="'.$name.'"]');
    	return (string)$itemArr[0]->value;
    }
    
    public function getAdminEmail() {
    	return $this->getConfig('admin_email');
    }
    
    public function getDatabaseHost() {
    	return $this->getConfig('db_host');
    }
    
    public function getDatabaseUser() {
    	return $this->getConfig('db_user');
    }
    
    public function getDatabasePassword() {
    	return $this->getConfig('db_password');
    }
    
    public function getDatabaseName() {
    	return $this->getConfig('db_name');
    }
    
    public function getManagerHost() {
    	return $this->getConfig('manager_host');
    }
    
    public function getManagerDaemonPort() {
    	return $this->getConfig('manager_daemon_port');
    }
    
    public function getManagerDataPort() {
    	return $this->getConfig('manager_data_port');
    }
    
    public function getManagerPhpPort() {
    	return $this->getConfig('manager_php_port');
    }
    
    public function getDaemonStatuses() {
    	return $this->genericGet('daemonstatuses');
    }
    
    public function getDaemonActions() {
    	return $this->genericGet('daemonactions');
    }
    
    public function getStatusList() {
    	return $this->genericGet('statuslist');
    }
    
    public function getFoldTypes() {
	    return $this->genericGet('foldtypes');
    }
    
   	public function getOutputTypes() {
   		return $this->genericGet('outputlist');
   	}
    
    public function getTaskParams() {
	    return $this->genericGet('taskparams');
    }
    
    public function getTaskOutputs() {
    	return $this->genericGet('taskoutputs');
    }
   
}
?>