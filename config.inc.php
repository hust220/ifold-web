<?php
/********************************************************************
* @name Config
* @abstract Include file that contains configuration parameters
* @since Feb 12, 2006
* -------------------------------------------------------------------/
*
* 				Jameson Lopp jameson@unc.edu
* @author		Adi Unnithan adi@unc.edu
*				Daniel Watson dcwatson@email.unc.edu
define('SMARTY_DIR', "/usr/share/php/smarty/");
*define('SMARTY_DIR', str_replace("\\","/",getcwd()). '/lib/smarty/libs/');
*********************************************************************/

define('IFOLD_DIR', str_replace("\\","/",getcwd()).'/');
define('SMARTY_DIR', str_replace("\\","/",getcwd()). '/lib/smarty/libs/');
define('UPLOAD_DIR', IFOLD_DIR . 'iFoldManager/uploads/');
define('DOWNLOAD_DIR', 'http://redshift.med.unc.edu/ifold/iFoldManager/uploads');
define('PROPS_PATH', IFOLD_DIR . "config/properties.xml");

require_once IFOLD_DIR . "lib/adodb/adodb.inc.php";
require_once IFOLD_DIR . "lib/adodb/adodb-exceptions.inc.php";
require_once IFOLD_DIR . "lib/SmartySetup.class.php";
require_once IFOLD_DIR . "lib/IFoldDB.class.php"; 
require_once IFOLD_DIR . "lib/IFoldProps.class.php";
require_once IFOLD_DIR . "lib/UserDAO.class.php";

session_start();

$smarty =& SmartyIfold::getSmarty();
$conn =& IFoldDB::getConn();

?>
