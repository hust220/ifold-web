<?php
/********************************************************************
* @name SmartySetup
* @abstract - Initializes Smarty by defining directories, variables
* @since Feb 12, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
*********************************************************************/
 
require_once SMARTY_DIR . 'Smarty.class.php';
require_once IFOLD_DIR . 'lib/IFoldProps.class.php';
require_once IFOLD_DIR . 'lib/TaskDAO.class.php';
require_once IFOLD_DIR . 'lib/DaemonDAO.class.php';

class SmartyIfold extends Smarty {

   	function SmartyIfold() {
   		$this->Smarty ();
   		$this->template_dir = IFOLD_DIR . '/templates/';
        $this->compile_dir  = IFOLD_DIR . '/templates_c/';
        $this->config_dir   = IFOLD_DIR . '/config/';
        $this->cache_dir 	= IFOLD_DIR . '/cache/';

        $this->caching = false;
        $this->assign ('app_name', 'iFold');
   	}
   	
   	public static function& getSmarty() {
   		if (! isset($_SESSION['smartyIfold'])) {
   			$_SESSION['smartyIfold'] = serialize(new SmartyIfold());
   		}
   		$smarty = unserialize($_SESSION['smartyIfold']);
   		return $smarty;
   	}
   	
   	public static function setSmarty($smarty) {
   		$_SESSION['smartyIfold'] = serialize($smarty);	
   	}
   
	function display_page($content_template = "index.tpl") {
		$this->assign ('content_template', $content_template);
		$this->assign ('atg_working', TaskDAO::getNumWorking());
		$this->assign ('atg_waiting', TaskDAO::getNumWaiting());
		$this->assign ('daemonList', DaemonDAO::getAtAGlance());
		$props = new IFoldProps();
		$this->assign_by_ref('daemonstatuses', $props->getDaemonStatuses());
		$this->display ('loggedIn.tpl');	
   	}
   	
   	function display_welcome($content_template = "introduction.tpl") {
   		$this->assign ('content_template', $content_template);
   		$this->display ('welcome.tpl');
   	}
   	
}
?>
