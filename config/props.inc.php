<?php

$config['admin_email'] = 'ifold@listserv.unc.edu';

$foldtype['1'] = 'fold';
$foldtype['2'] = 'thermoscan';
$foldtype['3'] = 'anneal';
$foldtype['4'] = 'pfold';

$taskparams['1'] = 'foldtype';
$taskparams['2'] = 'pdbCode';
$taskparams['3'] = 'pdbFileName';
$taskparams['4'] = 'pdbDecoyFileName';
$taskparams['5'] = 'simTime';
$taskparams['6'] = 'numIterations';
$taskparams['7'] = 'initialTemp';
$taskparams['8'] = 'finalTemp';
$taskparams['9'] = 'heatExchCo';
$taskparams['10'] = 'transTemp';
$taskparams['11'] = 'temp1';
$taskparams['12'] = 'temp2';
$taskparams['13'] = 'temp3';
$taskparams['14'] = 'temp4';
$taskparams['15'] = 'temp5';
$taskparams['16'] = 'temp6';

$taskoutputs[] = 'task_id';
$taskoutputs[] = 'trajectoryModelType';
$taskoutputs[] = 'trajectoryMin';
$taskoutputs[] = 'trajectoryMax';
$taskoutputs[] = 'trajectoryInterval';
$taskoutputs[] = 'contactFrequencyMap';
$taskoutputs[] = 'cvVsTemp';
$taskoutputs[] = 'equilibriumOffset';
$taskoutputs[] = 'energyVsTemp';
$taskoutputs[] = 'energyVsTime';
$taskoutputs[] = 'radiusVsTime';

$foldstatus['1'] = 'Queued';
$foldstatus['2'] = 'Pending';
$foldstatus['3'] = 'Running';
$foldstatus['4'] = 'Processing';
$foldstatus['5'] = 'Complete';
$foldstatus['6'] = 'Paused';
$foldstatus['7'] = 'Terminated';
$foldstatus['8'] = 'Unknown';

$GLOBALS['config'] = $config;
$GLOBALS['taskparams'] = $taskparams;
$GLOBALS['taskoutputs'] = $taskoutputs;
$GLOBALS['foldstatus'] = $foldstatus;
