-- phpMyAdmin SQL Dump
-- version 2.7.0-pl1
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Apr 29, 2006 at 07:37 PM
-- Server version: 4.1.16
-- PHP Version: 4.3.11
-- 
-- Database: `ifold`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `daemons`
-- 

CREATE TABLE `daemons` (
  `id` int(11) NOT NULL auto_increment,
  `address` varchar(32) NOT NULL default '',
  `port` int(11) NOT NULL default '0',
  `status` tinyint(4) NOT NULL default '3',
  `action` tinyint(4) NOT NULL default '1',
  `taskId` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=280 ;

-- 
-- Dumping data for table `daemons`
-- 

INSERT INTO `daemons` VALUES (276, '152.19.36.1', 30004, 1, 2, 521);
INSERT INTO `daemons` VALUES (277, 'troll.med.unc.edu', 30003, 3, 2, 0);
INSERT INTO `daemons` VALUES (278, 'troll.med.unc.edu', 30001, 2, 1, 575);
INSERT INTO `daemons` VALUES (279, '152.19.36.1', 30002, 2, 1, 574);

-- --------------------------------------------------------

-- 
-- Table structure for table `helppages`
-- 

CREATE TABLE `helppages` (
  `id` int(11) unsigned NOT NULL auto_increment,
  `level` tinyint(4) NOT NULL default '0',
  `name` varchar(100) NOT NULL default '',
  `description` varchar(255) NOT NULL default '',
  `author` int(11) NOT NULL default '0',
  `created_on` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `modified_on` timestamp NOT NULL default '0000-00-00 00:00:00',
  `content` longtext NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=14 ;

-- 
-- Dumping data for table `helppages`
-- 

INSERT INTO `helppages` VALUES (2, 0, 'testing', '', 0, '0000-00-00 00:00:00', '0000-00-00 00:00:00', '<ul>\r\n	\r\n<li>Allowed if processing hasn’t begun on the task</li>\r\n	\r\n<li>You can only edit parameters specific to the fold type; changing the fold type is not allowed</li>\r\n	\r\n<li>Task deletion - removes from the queue, or if the task has already run, deletes it and any stored output</li>\r\n<li>another line<br /></li></ul>');
INSERT INTO `helppages` VALUES (3, 0, 'Viewing the Queue', '', 0, '0000-00-00 00:00:00', '0000-00-00 00:00:00', 'fasdfasdfasdfasdf');
INSERT INTO `helppages` VALUES (4, 0, 'Your Activity', '', 0, '0000-00-00 00:00:00', '0000-00-00 00:00:00', '<ul>\r\n<li>Displays a list of all your submitted tasks, which can be sorted by any given column value</li>\r\n<li>If a task is in the queue and hasn’t begun processing, you can still edit the parameters</li>\r\n</ul>');
INSERT INTO `helppages` VALUES (5, 5, 'Admin Functions', 'managing iFold', 0, '0000-00-00 00:00:00', '2006-04-21 12:01:31', '<ul>\r\n<li>something goes here</li>\r\n<li>and here</li>\r\n<li>whatnot</li>\r\n<li>more testing<br /></li></ul>');
INSERT INTO `helppages` VALUES (12, 123, 'qwerty', '', 0, '2006-04-22 14:54:15', '0000-00-00 00:00:00', '');

-- --------------------------------------------------------

-- 
-- Table structure for table `outputs`
-- 

CREATE TABLE `outputs` (
  `id` int(11) NOT NULL auto_increment,
  `task_id` int(11) NOT NULL default '0',
  `fileName` varchar(32) NOT NULL default '',
  `outputType` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=961 ;

-- 
-- Dumping data for table `outputs`
-- 

INSERT INTO `outputs` VALUES (335, 401, '401-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (336, 401, '401-10-echoRmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (337, 401, '401-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (338, 401, '401-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (339, 401, '401-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (340, 401, '401-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (341, 401, '401-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (342, 402, '402-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (343, 402, '402-10-echoRmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (344, 402, '402-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (345, 402, '402-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (346, 402, '402-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (347, 402, '402-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (348, 402, '402-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (349, 397, '397-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (350, 397, '397-10-echoRmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (351, 397, '397-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (352, 397, '397-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (353, 397, '397-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (354, 397, '397-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (355, 397, '397-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (356, 404, '404-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (357, 404, '404-10-echoRmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (358, 404, '404-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (359, 404, '404-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (360, 404, '404-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (361, 404, '404-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (362, 404, '404-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (363, 406, '406-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (364, 406, '406-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (365, 406, '406-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (366, 406, '406-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (367, 406, '406-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (368, 406, '406-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (369, 406, '406-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (370, 406, '406-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (371, 407, '407-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (372, 407, '407-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (373, 407, '407-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (374, 407, '407-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (375, 407, '407-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (376, 407, '407-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (377, 407, '407-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (378, 407, '407-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (379, 410, '410-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (380, 410, '410-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (381, 410, '410-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (382, 410, '410-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (383, 410, '410-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (384, 410, '410-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (385, 410, '410-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (386, 410, '410-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (387, 408, '408-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (388, 408, '408-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (389, 408, '408-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (390, 408, '408-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (391, 408, '408-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (392, 408, '408-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (393, 408, '408-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (394, 408, '408-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (395, 415, '415-6-pFold.report', 6);
INSERT INTO `outputs` VALUES (396, 415, '415-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (397, 415, '415-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (398, 416, '416-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (399, 416, '416-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (400, 416, '416-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (401, 416, '416-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (402, 416, '416-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (403, 416, '416-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (404, 416, '416-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (405, 417, '417-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (406, 417, '417-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (407, 417, '417-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (408, 417, '417-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (409, 417, '417-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (410, 417, '417-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (411, 417, '417-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (412, 417, '417-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (413, 419, '419-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (414, 419, '419-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (415, 419, '419-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (416, 419, '419-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (417, 419, '419-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (418, 419, '419-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (419, 419, '419-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (420, 419, '419-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (421, 413, '413-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (422, 413, '413-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (423, 413, '413-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (424, 413, '413-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (425, 413, '413-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (426, 413, '413-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (427, 413, '413-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (428, 413, '413-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (429, 421, '421-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (430, 421, '421-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (431, 421, '421-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (432, 421, '421-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (433, 421, '421-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (434, 421, '421-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (435, 421, '421-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (436, 421, '421-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (437, 420, '420-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (438, 420, '420-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (439, 420, '420-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (440, 423, '423-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (441, 423, '423-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (442, 423, '423-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (443, 423, '423-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (444, 423, '423-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (445, 423, '423-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (446, 423, '423-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (447, 423, '423-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (448, 420, '420-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (449, 420, '420-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (450, 420, '420-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (451, 420, '420-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (452, 420, '420-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (453, 427, '427-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (454, 427, '427-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (455, 427, '427-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (456, 427, '427-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (457, 427, '427-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (458, 427, '427-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (459, 427, '427-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (460, 427, '427-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (461, 428, '428-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (462, 428, '428-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (463, 428, '428-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (464, 428, '428-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (465, 428, '428-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (466, 428, '428-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (467, 428, '428-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (468, 428, '428-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (469, 429, '429-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (470, 429, '429-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (471, 429, '429-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (472, 429, '429-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (473, 429, '429-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (474, 429, '429-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (475, 429, '429-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (476, 429, '429-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (477, 425, '425-6-pFold.report', 6);
INSERT INTO `outputs` VALUES (478, 425, '425-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (479, 425, '425-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (480, 432, '432-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (481, 432, '432-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (482, 432, '432-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (483, 432, '432-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (484, 432, '432-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (485, 432, '432-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (486, 432, '432-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (487, 432, '432-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (488, 430, '430-6-pFold.report', 6);
INSERT INTO `outputs` VALUES (489, 430, '430-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (490, 430, '430-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (491, 440, '440-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (492, 440, '440-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (493, 440, '440-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (494, 440, '440-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (495, 440, '440-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (496, 440, '440-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (497, 440, '440-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (498, 440, '440-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (499, 442, '442-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (500, 442, '442-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (501, 442, '442-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (502, 442, '442-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (503, 442, '442-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (504, 442, '442-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (505, 442, '442-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (506, 433, '433-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (507, 433, '433-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (508, 433, '433-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (509, 433, '433-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (510, 433, '433-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (511, 433, '433-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (512, 433, '433-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (513, 433, '433-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (514, 444, '444-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (515, 444, '444-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (516, 444, '444-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (517, 444, '444-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (518, 444, '444-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (519, 444, '444-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (520, 444, '444-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (521, 445, '445-6-pFold.report', 6);
INSERT INTO `outputs` VALUES (522, 445, '445-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (523, 445, '445-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (524, 447, '447-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (525, 447, '447-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (526, 447, '447-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (527, 447, '447-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (528, 447, '447-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (529, 447, '447-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (530, 447, '447-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (531, 447, '447-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (532, 448, '448-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (533, 448, '448-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (534, 448, '448-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (535, 448, '448-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (536, 448, '448-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (537, 448, '448-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (538, 448, '448-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (539, 448, '448-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (540, 449, '449-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (541, 449, '449-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (542, 449, '449-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (543, 449, '449-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (544, 449, '449-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (545, 449, '449-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (546, 449, '449-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (547, 449, '449-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (548, 450, '450-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (549, 450, '450-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (550, 450, '450-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (551, 450, '450-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (552, 450, '450-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (553, 450, '450-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (554, 450, '450-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (555, 450, '450-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (556, 451, '451-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (557, 451, '451-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (558, 451, '451-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (559, 451, '451-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (560, 451, '451-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (561, 451, '451-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (562, 451, '451-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (563, 451, '451-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (564, 446, '446-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (565, 446, '446-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (566, 446, '446-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (567, 446, '446-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (568, 446, '446-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (569, 446, '446-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (570, 446, '446-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (571, 452, '452-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (572, 452, '452-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (573, 452, '452-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (574, 452, '452-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (575, 452, '452-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (578, 453, '453-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (579, 453, '453-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (580, 453, '453-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (581, 453, '453-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (582, 453, '453-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (583, 453, '453-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (584, 453, '453-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (585, 453, '453-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (586, 455, '455-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (587, 455, '455-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (588, 455, '455-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (589, 455, '455-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (590, 455, '455-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (591, 455, '455-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (592, 455, '455-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (593, 455, '455-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (594, 457, '457-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (595, 457, '457-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (596, 457, '457-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (597, 457, '457-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (598, 457, '457-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (599, 457, '457-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (600, 457, '457-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (601, 457, '457-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (602, 456, '456-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (603, 456, '456-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (604, 456, '456-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (605, 456, '456-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (606, 456, '456-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (607, 456, '456-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (608, 456, '456-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (609, 456, '456-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (610, 459, '459-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (611, 459, '459-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (612, 459, '459-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (613, 459, '459-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (614, 459, '459-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (615, 459, '459-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (616, 459, '459-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (617, 459, '459-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (618, 458, '458-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (619, 458, '458-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (620, 458, '458-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (621, 458, '458-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (622, 458, '458-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (623, 458, '458-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (624, 458, '458-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (625, 458, '458-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (629, 462, '462-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (630, 462, '462-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (631, 462, '462-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (632, 462, '462-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (633, 462, '462-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (634, 462, '462-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (635, 462, '462-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (636, 462, '462-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (637, 463, '463-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (638, 463, '463-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (639, 463, '463-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (640, 463, '463-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (641, 463, '463-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (642, 463, '463-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (643, 463, '463-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (644, 463, '463-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (646, 465, '465-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (647, 465, '465-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (653, 466, '466-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (654, 466, '466-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (655, 466, '466-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (656, 466, '466-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (657, 466, '466-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (658, 466, '466-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (659, 466, '466-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (660, 466, '466-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (661, 467, '467-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (662, 467, '467-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (663, 467, '467-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (664, 467, '467-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (665, 467, '467-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (666, 467, '467-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (667, 467, '467-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (668, 467, '467-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (669, 470, '470-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (670, 470, '470-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (671, 470, '470-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (672, 470, '470-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (673, 470, '470-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (674, 470, '470-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (675, 470, '470-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (676, 470, '470-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (677, 468, '468-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (679, 468, '468-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (680, 468, '468-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (681, 468, '468-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (682, 468, '468-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (683, 468, '468-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (684, 468, '468-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (685, 471, '471-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (686, 471, '471-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (687, 471, '471-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (688, 471, '471-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (689, 471, '471-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (690, 471, '471-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (691, 471, '471-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (692, 471, '471-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (693, 475, '475-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (694, 475, '475-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (695, 475, '475-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (696, 475, '475-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (697, 475, '475-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (698, 475, '475-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (699, 475, '475-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (700, 479, '479-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (701, 481, '481-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (702, 481, '481-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (703, 481, '481-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (704, 481, '481-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (705, 481, '481-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (706, 481, '481-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (707, 481, '481-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (708, 483, '483-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (709, 483, '483-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (710, 483, '483-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (711, 483, '483-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (712, 483, '483-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (713, 483, '483-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (714, 483, '483-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (715, 483, '483-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (716, 485, '485-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (717, 485, '485-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (718, 485, '485-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (719, 485, '485-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (720, 485, '485-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (721, 485, '485-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (722, 485, '485-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (723, 485, '485-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (724, 486, '486-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (725, 486, '486-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (726, 486, '486-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (727, 486, '486-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (728, 486, '486-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (729, 486, '486-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (730, 486, '486-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (731, 486, '486-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (732, 491, '491-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (733, 491, '491-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (734, 491, '491-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (735, 491, '491-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (736, 491, '491-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (737, 491, '491-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (738, 491, '491-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (739, 491, '491-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (740, 493, '493-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (741, 493, '493-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (742, 493, '493-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (743, 493, '493-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (744, 493, '493-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (745, 493, '493-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (746, 493, '493-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (747, 493, '493-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (748, 494, '494-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (749, 494, '494-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (750, 494, '494-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (751, 494, '494-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (752, 494, '494-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (753, 494, '494-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (754, 494, '494-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (755, 494, '494-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (756, 495, '495-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (757, 495, '495-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (758, 495, '495-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (759, 495, '495-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (760, 495, '495-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (761, 495, '495-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (762, 495, '495-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (763, 495, '495-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (764, 496, '496-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (765, 496, '496-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (766, 496, '496-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (767, 496, '496-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (768, 496, '496-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (769, 496, '496-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (770, 496, '496-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (771, 496, '496-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (772, 497, '497-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (773, 497, '497-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (774, 497, '497-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (775, 497, '497-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (776, 497, '497-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (777, 497, '497-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (778, 497, '497-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (779, 497, '497-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (780, 498, '498-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (781, 498, '498-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (782, 498, '498-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (783, 498, '498-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (784, 498, '498-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (785, 498, '498-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (786, 498, '498-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (787, 498, '498-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (788, 499, '499-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (789, 499, '499-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (790, 499, '499-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (791, 499, '499-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (792, 499, '499-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (793, 499, '499-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (794, 499, '499-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (795, 499, '499-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (796, 500, '500-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (797, 500, '500-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (798, 500, '500-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (799, 500, '500-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (800, 500, '500-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (801, 500, '500-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (802, 500, '500-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (803, 500, '500-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (804, 501, '501-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (805, 501, '501-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (806, 501, '501-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (807, 501, '501-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (808, 501, '501-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (809, 501, '501-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (810, 501, '501-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (811, 501, '501-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (812, 502, '502-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (813, 502, '502-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (814, 502, '502-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (815, 502, '502-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (816, 502, '502-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (817, 502, '502-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (818, 502, '502-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (819, 502, '502-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (820, 503, '503-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (821, 503, '503-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (822, 503, '503-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (823, 503, '503-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (824, 503, '503-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (825, 503, '503-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (826, 503, '503-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (827, 503, '503-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (828, 504, '504-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (829, 504, '504-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (830, 504, '504-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (831, 504, '504-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (832, 504, '504-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (833, 504, '504-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (834, 504, '504-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (835, 504, '504-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (836, 505, '505-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (837, 505, '505-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (838, 505, '505-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (839, 505, '505-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (840, 505, '505-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (841, 505, '505-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (842, 505, '505-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (843, 505, '505-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (844, 506, '506-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (845, 506, '506-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (846, 506, '506-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (847, 506, '506-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (848, 506, '506-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (849, 506, '506-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (850, 506, '506-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (851, 506, '506-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (852, 507, '507-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (853, 507, '507-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (854, 507, '507-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (855, 507, '507-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (856, 507, '507-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (857, 507, '507-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (858, 507, '507-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (859, 507, '507-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (860, 508, '508-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (861, 508, '508-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (862, 508, '508-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (863, 508, '508-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (864, 508, '508-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (865, 508, '508-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (866, 508, '508-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (867, 508, '508-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (916, 472, '472-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (917, 472, '472-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (918, 472, '472-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (919, 472, '472-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (920, 472, '472-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (921, 472, '472-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (922, 472, '472-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (923, 472, '472-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (924, 566, '566-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (925, 566, '566-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (926, 566, '566-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (927, 566, '566-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (928, 566, '566-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (929, 566, '566-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (930, 566, '566-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (931, 566, '566-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (932, 567, '567-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (933, 567, '567-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (934, 567, '567-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (935, 567, '567-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (936, 567, '567-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (937, 567, '567-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (938, 567, '567-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (939, 567, '567-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (940, 568, '568-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (941, 568, '568-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (942, 568, '568-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (943, 568, '568-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (944, 568, '568-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (945, 568, '568-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (946, 568, '568-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (947, 569, '569-6-pFold.report', 6);
INSERT INTO `outputs` VALUES (948, 570, '570-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (949, 570, '570-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (950, 570, '570-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (951, 570, '570-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (952, 570, '570-1-ContactFreqMaps.zip', 1);
INSERT INTO `outputs` VALUES (953, 573, '573-9-movFiles.zip', 9);
INSERT INTO `outputs` VALUES (954, 573, '573-10-echoFiles.zip', 10);
INSERT INTO `outputs` VALUES (955, 573, '573-10-rmsFiles.zip', 10);
INSERT INTO `outputs` VALUES (956, 573, '573-8-TrajectoryPDB.zip', 8);
INSERT INTO `outputs` VALUES (957, 573, '573-3-EnergyVsTempPlots.zip', 3);
INSERT INTO `outputs` VALUES (958, 573, '573-4-EnergyVsTimePlots.zip', 4);
INSERT INTO `outputs` VALUES (959, 573, '573-5-RadiusVsTimePlots.zip', 5);
INSERT INTO `outputs` VALUES (960, 573, '573-1-ContactFreqMaps.zip', 1);

-- --------------------------------------------------------

-- 
-- Table structure for table `taskoutputs`
-- 

CREATE TABLE `taskoutputs` (
  `id` int(11) NOT NULL auto_increment,
  `task_id` int(11) NOT NULL default '0',
  `trajModelType` int(11) NOT NULL default '0',
  `trajMin` int(11) NOT NULL default '0',
  `trajMax` int(11) NOT NULL default '0',
  `trajInterval` int(11) NOT NULL default '0',
  `contactFreqMap` tinyint(1) NOT NULL default '0',
  `cvVsTemp` tinyint(1) NOT NULL default '0',
  `equilOffset` int(11) NOT NULL default '0',
  `energyVsTemp` tinyint(1) NOT NULL default '0',
  `energyVsTime` tinyint(1) NOT NULL default '0',
  `radiusVsTime` tinyint(1) NOT NULL default '0',
  `mov` tinyint(4) NOT NULL default '0',
  `echo` tinyint(4) NOT NULL default '0',
  `rms` tinyint(4) NOT NULL default '0',
  `raw` tinyint(4) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=515 ;

-- 
-- Dumping data for table `taskoutputs`
-- 

INSERT INTO `taskoutputs` VALUES (364, 425, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (365, 426, 0, 0, 4000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (366, 427, 0, 0, 1000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (367, 428, 0, 0, 20000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (368, 429, 0, 0, 50000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (369, 430, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (370, 431, 0, 0, 45000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (371, 432, 0, 0, 3000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (372, 433, 0, 0, 50000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (373, 434, 0, 0, 60000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (374, 435, 0, 0, 30000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (375, 436, 0, 0, 10000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (376, 437, 0, 0, 11000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (400, 461, 0, 0, 20000, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (403, 464, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (410, 471, 0, 0, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (411, 472, 0, 0, 200, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (412, 473, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (413, 474, 0, 0, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (414, 475, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (415, 476, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (417, 478, 0, 0, 10000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (418, 479, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (419, 480, 0, 0, 1000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (420, 481, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (422, 483, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (423, 484, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (424, 485, 0, 0, 1000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (425, 486, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (426, 487, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (427, 488, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (428, 489, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (429, 490, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (430, 491, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (431, 492, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (432, 493, 0, 0, 85000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (487, 548, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (488, 549, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (489, 550, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (490, 551, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (491, 552, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (492, 553, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (493, 554, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (494, 555, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (495, 556, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (496, 557, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (497, 558, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (498, 559, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (499, 560, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (500, 561, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (501, 562, 0, 0, 1000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (502, 563, 0, 0, 10000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (503, 564, 0, 0, 10000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (505, 566, 0, 0, 35000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (506, 567, 0, 0, 10000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (507, 568, 0, 1, 100000, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (510, 571, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (511, 572, 0, 0, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (512, 573, 0, 10000, 35000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (513, 574, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskoutputs` VALUES (514, 575, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

-- 
-- Table structure for table `taskparams`
-- 

CREATE TABLE `taskparams` (
  `id` int(11) NOT NULL auto_increment,
  `foldtype` int(11) NOT NULL default '0',
  `pdbCode` varchar(4) NOT NULL default '',
  `pdbFileName` varchar(32) NOT NULL default '',
  `pdbDecoyFileName` varchar(32) NOT NULL default '',
  `modelType` int(11) NOT NULL default '0',
  `simTime` int(11) NOT NULL default '0',
  `numIterations` int(11) NOT NULL default '0',
  `initialTemp` float NOT NULL default '0',
  `finalTemp` float NOT NULL default '0',
  `heatExchCo` float NOT NULL default '0',
  `transTemp` float NOT NULL default '0',
  `temp1` float NOT NULL default '0',
  `temp2` float NOT NULL default '0',
  `temp3` float NOT NULL default '0',
  `temp4` float NOT NULL default '0',
  `temp5` float NOT NULL default '0',
  `temp6` float NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=335 ;

-- 
-- Dumping data for table `taskparams`
-- 

INSERT INTO `taskparams` VALUES (195, 2, '1', '', '', 1, 60000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (196, 1, '2ci2', '', '', 2, 30000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (197, 2, '1spd', '', '', 2, 25000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (198, 2, '1mjc', '', '', 2, 20000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (222, 4, '2EBN', '', '', 2, 20000, 5, 1, 0.3, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (225, 1, '3CHY', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (232, 1, '1nlo', '', '', 2, 200, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (233, 1, '3chy', '', '', 2, 200, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (234, 1, 'asss', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (235, 1, '1ubq', '', '', 2, 1000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (236, 1, '1spd', '', '', 2, 100, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (237, 2, '1ubq', '', '', 2, 100, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (239, 1, '3CHY', '', '', 2, 100, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (240, 1, '1ubq', '', '', 2, 100, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (241, 1, 'sdsd', '', '', 2, 1000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (242, 1, '1SPD', '', '', 2, 100, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (244, 1, '1ubq', '', '', 2, 100, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (245, 1, '2ci2', '', '', 2, 100, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (246, 1, '1ubq', '', '', 2, 1000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (247, 1, '1ubq', '', '', 2, 100, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (248, 2, 'asds', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (249, 1, 'asas', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (250, 1, 'asda', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (251, 2, 'sads', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (252, 1, '1ubq', '', '', 2, 100, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (253, 1, 'wwww', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (254, 1, '3chy', '', '', 2, 85000, 0, 0.1, 2.3, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (267, 1, '3CHY', '', '', 2, 10000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (276, 1, '3CHY', '', '', 2, 1000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (277, 1, '3CHY', '', '', 2, 1000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (279, 1, '3CHY', '', '', 2, 1000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (280, 1, 'f323', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (282, 1, 'lskd', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (309, 1, 'aois', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (310, 1, 'alsj', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (311, 1, 'laks', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (312, 1, 'asdf', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (313, 1, 'lsak', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (314, 1, 'q', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (315, 1, 'ij', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (316, 1, '[po[', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (317, 1, ',.m.', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (318, 1, 'oiwj', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (319, 1, 'lasj', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (320, 1, 'aksj', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (321, 1, '3CHY', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (322, 1, '3CHY', '', '', 2, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (323, 1, '3CHY', '', '', 2, 1000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (324, 1, '3CHY', '', '', 2, 10000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (325, 2, '3CHY', '', '', 2, 10000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (327, 1, '3chy', '', '', 2, 35000, 0, 0.01, 2.678, 0.0005, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (328, 1, '3CHY', '', '', 2, 10000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (329, 1, '1spd', '', '', 4, 100000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (332, 1, '2acy', '', '', 2, 45000, 0, 0.4, 1.2, 0.0001, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (333, 5, '', '574-pdbFileName', '574-pdbDecoyFileName', 2, 0, 15, 0, 0, 0, 0.35, 0, 0, 0, 0, 0, 0);
INSERT INTO `taskparams` VALUES (334, 3, '1mjc', '', '', 2, 20000, 0, 0, 0, 0, 0, 0.6, 0.7, 0.8, 0.9, 1, 0);

-- --------------------------------------------------------

-- 
-- Table structure for table `tasks`
-- 

CREATE TABLE `tasks` (
  `id` int(11) NOT NULL auto_increment,
  `param_id` int(11) NOT NULL default '0',
  `name` varchar(60) NOT NULL default '',
  `description` varchar(255) NOT NULL default '',
  `created_on` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `created_by` int(11) NOT NULL default '0',
  `started_on` timestamp NOT NULL default '0000-00-00 00:00:00',
  `completed_on` timestamp NOT NULL default '0000-00-00 00:00:00',
  `status` varchar(32) NOT NULL default '1',
  `queuenum` int(11) NOT NULL default '0',
  `daemon_uri` varchar(100) NOT NULL default '',
  `messages` text NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=576 ;

-- 
-- Dumping data for table `tasks`
-- 

INSERT INTO `tasks` VALUES (550, 311, 'laksjdflk', 'lkjsadlkfj', '2006-04-25 04:44:22', 1, '2006-04-25 04:44:22', '2006-04-25 04:44:22', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nError: Could not retrieve native PDB\n');
INSERT INTO `tasks` VALUES (551, 312, 'lkasjlf', 'salkdjfab', '2006-04-25 04:44:48', 1, '2006-04-25 04:44:48', '2006-04-25 04:44:49', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nError: Could not retrieve native PDB\n');
INSERT INTO `tasks` VALUES (552, 313, 'jalskv', ',ms,f', '2006-04-25 04:45:24', 1, '2006-04-25 04:45:24', '2006-04-25 04:45:24', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nError: Could not retrieve native PDB\n');
INSERT INTO `tasks` VALUES (553, 314, 'que', 'qq', '2006-04-25 04:45:31', 1, '2006-04-25 04:45:31', '2006-04-25 04:45:31', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nError: Could not retrieve native PDB\n');
INSERT INTO `tasks` VALUES (554, 315, 'o9ipi', 'oipoi', '2006-04-25 04:45:42', 1, '2006-04-25 04:45:42', '2006-04-25 04:45:43', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nError: Could not retrieve native PDB\n');
INSERT INTO `tasks` VALUES (555, 316, 'p[qepo', 'powe', '2006-04-25 04:45:51', 1, '2006-04-25 04:45:51', '2006-04-25 04:45:52', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nError: Could not retrieve native PDB\n');
INSERT INTO `tasks` VALUES (556, 317, ',.mx.,m', '.,m.m', '2006-04-25 04:46:01', 1, '2006-04-25 04:46:01', '2006-04-25 04:46:03', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nError: Could not retrieve native PDB\n');
INSERT INTO `tasks` VALUES (557, 318, 'oije', 'oij', '2006-04-25 04:46:09', 1, '2006-04-25 04:46:09', '2006-04-25 04:46:10', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nError: Could not retrieve native PDB\n');
INSERT INTO `tasks` VALUES (558, 319, 'poiw992', '903', '2006-04-25 04:46:19', 1, '2006-04-25 04:46:19', '2006-04-25 04:46:19', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nError: Could not retrieve native PDB\n');
INSERT INTO `tasks` VALUES (559, 320, 'lkasjflk', 'jalskdjf', '2006-04-25 04:48:58', 1, '2006-04-25 04:48:58', '2006-04-25 04:48:59', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nError: Could not retrieve native PDB\n');
INSERT INTO `tasks` VALUES (560, 321, 'alksjfdlk', 'lkajslkfdj', '2006-04-25 04:49:13', 1, '2006-04-25 04:49:13', '2006-04-25 04:49:14', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nMessage: Got native PDB.\nError: Could not prepare PDB: 3chy.pdb\n');
INSERT INTO `tasks` VALUES (561, 322, 'mx,.m', ',.smdf.,', '2006-04-25 04:49:23', 1, '2006-04-25 04:49:24', '2006-04-25 04:49:25', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nMessage: Got native PDB.\nError: Could not prepare PDB: 3chy.pdb\n');
INSERT INTO `tasks` VALUES (562, 323, 'lkajoiwejoi', 'asoijfalksjd', '2006-04-25 04:49:38', 1, '2006-04-25 04:49:38', '2006-04-25 04:49:39', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nMessage: Got native PDB.\nError: Could not prepare PDB: 3chy.pdb\n');
INSERT INTO `tasks` VALUES (563, 324, 'lakjsdj', 'jlkasjfd', '2006-04-25 04:50:17', 1, '2006-04-25 04:50:17', '2006-04-25 04:50:17', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nMessage: Got native PDB.\nError: Could not prepare PDB: 3chy.pdb\n');
INSERT INTO `tasks` VALUES (564, 325, 'asdfsfd', 'lkasd', '2006-04-25 05:05:41', 1, '2006-04-25 05:05:42', '2006-04-25 05:05:42', '5', 1, 'troll.med.unc.edu:30001', 'Message: Fold type detected.\nMessage: Got native PDB.\nError: Could not prepare PDB: 3chy.pdb\n');
INSERT INTO `tasks` VALUES (566, 327, 'sadsad', 'dasdasd', '2006-04-25 11:31:26', 27, '2006-04-25 11:31:26', '2006-04-25 12:39:36', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nMessage: Got native PDB.\nMessage: Prepared native PDB.\nMessage: Executed Fold script.\nMessage: Sent output file: 566-9-movFiles.zip\nMessage: Sent output file: 566-10-echoFiles.zip\nMessage: Sent output file: 566-10-rmsFiles.zip\nMessage: Sent output file: 566-8-TrajectoryPDB.zip\nMessage: Sent output file: 566-3-EnergyVsTempPlots.zip\nMessage: Sent output file: 566-4-EnergyVsTimePlots.zip\nMessage: Sent output file: 566-5-RadiusVsTimePlots.zip\nMessage: Sent output file: 566-1-ContactFreqMaps.zip\nMessage: Successfully ran Unfold.\n');
INSERT INTO `tasks` VALUES (567, 328, 'lkasjdf', 'asdk', '2006-04-25 16:25:26', 1, '2006-04-25 16:25:27', '2006-04-25 16:37:40', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nMessage: Got native PDB.\nMessage: Prepared native PDB.\nMessage: Executed Fold script.\nMessage: Sent output file: 567-9-movFiles.zip\nMessage: Sent output file: 567-10-echoFiles.zip\nMessage: Sent output file: 567-10-rmsFiles.zip\nMessage: Sent output file: 567-8-TrajectoryPDB.zip\nMessage: Sent output file: 567-3-EnergyVsTempPlots.zip\nMessage: Sent output file: 567-4-EnergyVsTimePlots.zip\nMessage: Sent output file: 567-5-RadiusVsTimePlots.zip\nMessage: Sent output file: 567-1-ContactFreqMaps.zip\nMessage: Successfully ran Unfold.\n');
INSERT INTO `tasks` VALUES (568, 329, '1spd', '1spd', '2006-04-25 20:17:53', 23, '2006-04-25 20:17:53', '2006-04-26 04:47:18', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nMessage: Got native PDB.\nMessage: Prepared native PDB.\nMessage: Executed Fold script.\nMessage: Sent output file: 568-9-movFiles.zip\nMessage: Sent output file: 568-10-echoFiles.zip\nMessage: Sent output file: 568-10-rmsFiles.zip\nError: Could not read output file: TrajectoryPDB.zip\nMessage: Sent output file: 568-3-EnergyVsTempPlots.zip\nMessage: Sent output file: 568-4-EnergyVsTimePlots.zip\nMessage: Sent output file: 568-5-RadiusVsTimePlots.zip\nMessage: Sent output file: 568-1-ContactFreqMaps.zip\nMessage: Successfully ran Unfold.\n');
INSERT INTO `tasks` VALUES (571, 0, 'fn3', 'fn3 thermo scan', '2006-04-28 17:27:45', 26, '2006-04-28 17:27:46', '2006-04-28 17:27:46', '5', 1, 'troll.med.unc.edu:30001', 'Error: Task type not mapped yet.\n');
INSERT INTO `tasks` VALUES (572, 0, 'fn3 unfold', 'fn3 unfold', '2006-04-28 17:33:47', 26, '2006-04-28 17:33:47', '2006-04-28 17:33:48', '5', 1, 'troll.med.unc.edu:30001', 'Error: Task type not mapped yet.\n');
INSERT INTO `tasks` VALUES (573, 332, '2ci2Task', 'adsasd', '2006-04-29 17:54:29', 27, '2006-04-29 17:54:29', '2006-04-29 18:31:51', '5', 1, 'troll.med.unc.edu:30001', 'Message: Unfold type detected.\nMessage: Got native PDB.\nMessage: Prepared native PDB.\nMessage: Executed Fold script.\nMessage: Sent output file: 573-9-movFiles.zip\nMessage: Sent output file: 573-10-echoFiles.zip\nMessage: Sent output file: 573-10-rmsFiles.zip\nMessage: Sent output file: 573-8-TrajectoryPDB.zip\nMessage: Sent output file: 573-3-EnergyVsTempPlots.zip\nMessage: Sent output file: 573-4-EnergyVsTimePlots.zip\nMessage: Sent output file: 573-5-RadiusVsTimePlots.zip\nMessage: Sent output file: 573-1-ContactFreqMaps.zip\nMessage: Successfully ran Unfold.\n');
INSERT INTO `tasks` VALUES (574, 333, 'pFoldTest', 'testing pfold', '2006-04-29 17:55:29', 27, '2006-04-29 17:55:29', '0000-00-00 00:00:00', '3', 1, '152.19.36.1:30002', '');
INSERT INTO `tasks` VALUES (575, 334, '1mjcThermo', 'descr', '2006-04-29 19:21:49', 27, '2006-04-29 19:21:49', '0000-00-00 00:00:00', '3', 1, 'troll.med.unc.edu:30001', '');

-- --------------------------------------------------------

-- 
-- Table structure for table `users`
-- 

CREATE TABLE `users` (
  `id` int(11) NOT NULL auto_increment,
  `created_on` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `username` varchar(60) NOT NULL default '',
  `password` varchar(60) NOT NULL default '',
  `namefirst` varchar(60) NOT NULL default '',
  `namelast` varchar(60) NOT NULL default '',
  `level` tinyint(4) NOT NULL default '1',
  `email` varchar(100) NOT NULL default '',
  `organization` varchar(100) NOT NULL default '',
  `numtasks` int(10) NOT NULL default '10',
  `cpuHours` int(11) NOT NULL default '100',
  `emailConfirmed` tinyint(1) unsigned NOT NULL default '0',
  `approved` tinyint(1) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=41 ;

-- 
-- Dumping data for table `users`
-- 

INSERT INTO `users` VALUES (1, '2006-04-25 04:59:39', 'adi', 'blahblah', 'Adi', 'Unnithan', 9, 'adi@unc.edu', 'UNC-Chapel Hill', 1000, 100, 1, 1);
INSERT INTO `users` VALUES (22, '2006-04-24 16:11:30', 'fusion', 'default', 'jameson', 'lopp', 9, 'fusion@email.unc.edu', 'UNC', 100, 46, 1, 1);
INSERT INTO `users` VALUES (23, '2006-03-02 17:54:29', 'dokh', 'zaraza', 'Nikolay', 'Dokholyan', 1, 'dokh@email.unc.edu', 'UNC-Chapel Hill', 10, 100, 1, 1);
INSERT INTO `users` VALUES (24, '2006-02-28 11:35:36', 'shantanu', 'shantanu', 'Shantanu', 'Sharma', 1, 'shantanu@unc.edu', 'UNC Chapel Hill', 10, 100, 1, 1);
INSERT INTO `users` VALUES (25, '2006-03-02 17:50:35', 'fding', 'zaq12wsx', 'Feng', 'Ding', 1, 'fding@unc.edu', 'UNC-Chapel Hill', 10, 100, 1, 1);
INSERT INTO `users` VALUES (26, '2006-03-27 01:11:30', 'hfnie', 'room302', 'Huifen', 'Nie', 1, 'hfnie@email.unc.edu', 'UNC-Chapel Hill', 10, 100, 1, 1);
INSERT INTO `users` VALUES (27, '2006-04-20 22:45:42', 'bigdandcw', '840311', 'Daniel', 'Watson', 9, 'dcwatson84@gmail.com', 'UNC-Chapel Hill', 100, 100, 1, 1);
INSERT INTO `users` VALUES (35, '2006-04-18 17:00:14', 'dpoz22', 'dpozdpoz', 'Diane', 'Pozefsky', 9, 'pozefsky@cs.unc', 'CS', 145, 10, 0, 1);
INSERT INTO `users` VALUES (38, '2006-04-18 23:19:29', 'aditest', 'if0ldr0ck5!', 'Adi', 'Unnithan', 1, 'adi@unc.edu', 'UNC', 10, 100, 1, 1);
INSERT INTO `users` VALUES (39, '2006-04-18 20:39:57', 'dcwatson', '840311', 'Daniel', 'Watson', 1, 'danielwatson@yahoo.com', 'UNC-CH', 100, 100, 0, 1);
INSERT INTO `users` VALUES (40, '2006-04-18 23:19:23', 'dianetest', 'lauren', 'Diane', 'Poz', 9, 'pozefsky@cs.unc.edu', 'UNC', 100, 100, 1, 1);
