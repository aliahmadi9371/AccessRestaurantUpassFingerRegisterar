/*
 Navicat Premium Data Transfer

 Source Server         : 192.168.1.90Win
 Source Server Type    : MySQL
 Source Server Version : 50727
 Source Host           : 192.168.1.90:3306
 Source Schema         : AsaController

 Target Server Type    : MySQL
 Target Server Version : 50727
 File Encoding         : 65001

 Date: 27/10/2019 21:58:18
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for access_group_terminals
-- ----------------------------
DROP TABLE IF EXISTS `access_group_terminals`;
CREATE TABLE `access_group_terminals`  (
  `id` int(11) NOT NULL,
  `access_group_fr` smallint(6) NOT NULL,
  `terminal_fr` int(11) NOT NULL,
  `created_at` datetime(0) NULL DEFAULT NULL,
  `updated_at` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `access_group_terminals_access_group_fr_foreign`(`access_group_fr`) USING BTREE,
  INDEX `access_group_terminals_terminal_fr_foreign`(`terminal_fr`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_persian_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for access_groups_details
-- ----------------------------
DROP TABLE IF EXISTS `access_groups_details`;
CREATE TABLE `access_groups_details`  (
  `id` int(11) NOT NULL,
  `access_group_fr` smallint(6) NOT NULL,
  `access_time_fr` smallint(6) NOT NULL,
  `created_at` datetime(0) NULL DEFAULT NULL,
  `updated_at` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `access_groups_details_access_group_fr_foreign`(`access_group_fr`) USING BTREE,
  INDEX `access_groups_details_access_time_fr_foreign`(`access_time_fr`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_persian_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for access_times
-- ----------------------------
DROP TABLE IF EXISTS `access_times`;
CREATE TABLE `access_times`  (
  `id` smallint(6) NOT NULL,
  `name` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `holiday_fr` smallint(6) NULL DEFAULT NULL,
  `created_at` datetime(0) NULL DEFAULT NULL,
  `updated_at` datetime(0) NULL DEFAULT NULL,
  `send_status` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `srv_last_update` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `access_times_name_unique`(`name`) USING BTREE,
  INDEX `access_times_holiday_fr_foreign`(`holiday_fr`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_persian_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for access_times_details
-- ----------------------------
DROP TABLE IF EXISTS `access_times_details`;
CREATE TABLE `access_times_details`  (
  `id` int(11) NOT NULL,
  `access_time_fr` smallint(6) NOT NULL,
  `dayOfWeek` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `time_zone_fr` smallint(6) NOT NULL,
  `created_at` datetime(0) NULL DEFAULT NULL,
  `updated_at` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `access_times_details_access_time_fr_foreign`(`access_time_fr`) USING BTREE,
  INDEX `access_times_details_time_zone_fr_foreign`(`time_zone_fr`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_persian_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for holidays_details
-- ----------------------------
DROP TABLE IF EXISTS `holidays_details`;
CREATE TABLE `holidays_details`  (
  `id` int(11) NOT NULL,
  `holiday_fr` smallint(6) NOT NULL,
  `holiday_date` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `main_date` datetime(0) NOT NULL,
  `created_at` datetime(0) NULL DEFAULT NULL,
  `updated_at` datetime(0) NULL DEFAULT NULL,
  `holiday_month` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `holiday_day` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `holidays_details_holiday_fr_foreign`(`holiday_fr`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_persian_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for personnel_access_groups
-- ----------------------------
DROP TABLE IF EXISTS `personnel_access_groups`;
CREATE TABLE `personnel_access_groups`  (
  `id` int(11) NOT NULL,
  `access_group_fr` smallint(6) NOT NULL,
  `real_user_fr` int(11) NOT NULL,
  `description` longtext CHARACTER SET utf8 COLLATE utf8_persian_ci NULL,
  `status` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `archived` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `archivedDesc` longtext CHARACTER SET utf8 COLLATE utf8_persian_ci NULL,
  `archiveTime` datetime(0) NULL DEFAULT NULL,
  `created_at` datetime(0) NULL DEFAULT NULL,
  `updated_at` datetime(0) NULL DEFAULT NULL,
  `send_status` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `srv_last_update` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `personnel_access_groups_access_group_fr_foreign`(`access_group_fr`) USING BTREE,
  INDEX `personnel_access_groups_real_user_fr_foreign`(`real_user_fr`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_persian_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for serv_access_logs
-- ----------------------------
DROP TABLE IF EXISTS `serv_access_logs`;
CREATE TABLE `serv_access_logs`  (
  `id` bigint(20) NOT NULL,
  `real_user_fr` int(11) NULL DEFAULT NULL,
  `terminalId` int(11) NULL DEFAULT NULL,
  `rfId` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `authMode` int(11) NULL DEFAULT NULL,
  `authType` int(11) NULL DEFAULT NULL,
  `year` int(11) NULL DEFAULT NULL,
  `month` int(11) NULL DEFAULT NULL,
  `day` int(11) NULL DEFAULT NULL,
  `hour` int(11) NULL DEFAULT NULL,
  `min` int(11) NULL DEFAULT NULL,
  `sec` int(11) NULL DEFAULT NULL,
  `authError` int(11) NULL DEFAULT NULL,
  `isAuth` tinyint(4) NULL DEFAULT NULL,
  `created_at` datetime(0) NULL DEFAULT NULL,
  `updated_at` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `serv_access_logs_real_user_fr_foreign`(`real_user_fr`) USING BTREE,
  INDEX `serv_access_logs_terminalid_foreign`(`terminalId`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_persian_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for serv_terminal_status
-- ----------------------------
DROP TABLE IF EXISTS `serv_terminal_status`;
CREATE TABLE `serv_terminal_status`  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `terminalId` int(11) NULL DEFAULT NULL,
  `terminal` int(11) NULL DEFAULT NULL,
  `door` int(11) NULL DEFAULT NULL,
  `cover` int(11) NULL DEFAULT NULL,
  `lock` int(11) NULL DEFAULT NULL,
  `open` int(11) NULL DEFAULT NULL,
  `created_at` datetime(0) NULL DEFAULT NULL,
  `updated_at` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `serv_terminal_status_terminalid_foreign`(`terminalId`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 65936 CHARACTER SET = utf8 COLLATE = utf8_persian_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for tags
-- ----------------------------
DROP TABLE IF EXISTS `tags`;
CREATE TABLE `tags`  (
  `id` int(11) NOT NULL,
  `tagName` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `tagId` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `mainItem` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `car` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `carId` int(11) NULL DEFAULT NULL,
  `color` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `colorId` int(11) NULL DEFAULT NULL,
  `visitName` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `visitId` int(11) NULL DEFAULT NULL,
  `receivedObj` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `activeTagDescription` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `real_user_fr` int(11) NOT NULL,
  `active` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `archived` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `status` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `car_fr` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `archivedTime` datetime(0) NULL DEFAULT NULL,
  `replica` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `printer` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `rejectReason` longtext CHARACTER SET utf8 COLLATE utf8_persian_ci NULL,
  `created_at` datetime(0) NULL DEFAULT NULL,
  `updated_at` datetime(0) NULL DEFAULT NULL,
  `option1` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `option2` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `option3` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `active_templateId` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `revival` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `cardPresso` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `sendToTerminal` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `lastUpdateTerminalStatus` datetime(0) NULL DEFAULT NULL,
  `cardReader` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `tags_real_user_fr_foreign`(`real_user_fr`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_persian_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for terminals
-- ----------------------------
DROP TABLE IF EXISTS `terminals`;
CREATE TABLE `terminals`  (
  `id` int(11) NOT NULL,
  `terminalId` int(11) NOT NULL,
  `terminalIp` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `name` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `created_at` datetime(0) NULL DEFAULT NULL,
  `updated_at` datetime(0) NULL DEFAULT NULL,
  `site` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `door` longtext CHARACTER SET utf8 COLLATE utf8_persian_ci NULL,
  `direction` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `send_status` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `srv_last_update` datetime(0) NULL DEFAULT NULL,
  `archived` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `status_terminal` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `status_time_zone` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `status_holiday` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `status_access_time` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `status_access_group` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `type` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `terminals_terminalid_unique`(`terminalId`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_persian_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for time_zones_details
-- ----------------------------
DROP TABLE IF EXISTS `time_zones_details`;
CREATE TABLE `time_zones_details`  (
  `id` int(11) NOT NULL,
  `number` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NULL DEFAULT NULL,
  `start_hour` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `start_minute` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `end_hour` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `end_minute` varchar(191) CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `time_zone_fr` smallint(6) NOT NULL,
  `created_at` datetime(0) NULL DEFAULT NULL,
  `updated_at` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `time_zones_details_time_zone_fr_foreign`(`time_zone_fr`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_persian_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Procedure structure for sp_upass_query
-- ----------------------------
DROP PROCEDURE IF EXISTS `sp_upass_query`;
delimiter ;;
CREATE PROCEDURE `sp_upass_query`(IN TagNumber VARCHAR(30), IN TerminalId INT)
BEGIN 
		IF EXISTS(
							SELECT DISTINCT
							DATE(AsaController.holidays_details.main_date)
							FROM
							AsaController.tags
							INNER JOIN AsaController.personnel_access_groups ON AsaController.tags.real_user_fr = AsaController.personnel_access_groups.real_user_fr
							INNER JOIN AsaController.access_groups_details ON AsaController.personnel_access_groups.access_group_fr = AsaController.access_groups_details.access_group_fr
							INNER JOIN AsaController.access_group_terminals ON AsaController.access_groups_details.access_group_fr = AsaController.access_group_terminals.access_group_fr
							INNER JOIN AsaController.terminals ON AsaController.access_group_terminals.terminal_fr = AsaController.terminals.id
							INNER JOIN AsaController.access_times ON AsaController.access_groups_details.access_time_fr = AsaController.access_times.id
							INNER JOIN AsaController.holidays_details ON AsaController.access_times.holiday_fr = AsaController.holidays_details.holiday_fr
							WHERE
							DATE(AsaController.holidays_details.main_date) = DATE(CURDATE())
				)THEN SELECT DISTINCT
							AsaController.tags.mainItem,

							CONCAT(CURDATE(),' ',AsaController.time_zones_details.start_hour, ':',AsaController.time_zones_details.start_minute) AS startTime,
							CONCAT(CURDATE(),' ',AsaController.time_zones_details.end_hour, ':',AsaController.time_zones_details.end_minute) AS endTime,
							AsaController.access_times_details.dayOfWeek,
							AsaController.tags.real_user_fr,
							AsaController.terminals.terminalId,
							AsaController.terminals.type
							FROM
							AsaController.tags
							INNER JOIN AsaController.personnel_access_groups ON AsaController.tags.real_user_fr = AsaController.personnel_access_groups.real_user_fr
							INNER JOIN AsaController.access_groups_details ON AsaController.access_groups_details.access_group_fr = AsaController.personnel_access_groups.access_group_fr
							INNER JOIN AsaController.access_times ON AsaController.access_groups_details.access_time_fr = AsaController.access_times.id
							INNER JOIN AsaController.access_times_details ON AsaController.access_times_details.access_time_fr = AsaController.access_times.id
							INNER JOIN AsaController.time_zones_details ON AsaController.time_zones_details.time_zone_fr = AsaController.access_times_details.time_zone_fr
							INNER JOIN AsaController.access_group_terminals ON AsaController.access_group_terminals.access_group_fr = AsaController.personnel_access_groups.access_group_fr
							INNER JOIN AsaController.terminals ON AsaController.access_group_terminals.terminal_fr = AsaController.terminals.id
							WHERE
							AsaController.tags.tagId = '5' AND
							AsaController.tags.mainItem = TagNumber AND
							AsaController.terminals.terminalId = TerminalId AND
							AsaController.terminals.type = 'UPass' AND
							AsaController.access_times_details.dayOfWeek = 0 AND
							TIME(now()) >= TIME(CONCAT(AsaController.time_zones_details.start_hour, ':',AsaController.time_zones_details.start_minute , ':00')) and
							TIME(now()) <= TIME(CONCAT(AsaController.time_zones_details.end_hour, ':',AsaController.time_zones_details.end_minute, ':00'))  and
-- 							CONCAT(CURDATE(),' ',AsaController.time_zones_details.start_hour, ':',AsaController.time_zones_details.start_minute) <= DATE_FORMAT(CURRENT_TIMESTAMP(), '%Y-%m-%d %k:%i') AND
-- 							CONCAT(CURDATE(),' ',AsaController.time_zones_details.end_hour, ':',AsaController.time_zones_details.end_minute) >=  DATE_FORMAT(CURRENT_TIMESTAMP(), '%Y-%m-%d %k:%i')AND
							AsaController.personnel_access_groups.archived is NULL AND
							AsaController.terminals.archived is NULL AND
							AsaController.tags.archived is NULL;
					ELSE
						SELECT DISTINCT
							AsaController.tags.mainItem,
							CONCAT(CURDATE(),' ',AsaController.time_zones_details.start_hour, ':',AsaController.time_zones_details.start_minute) AS startTime,
							CONCAT(CURDATE(),' ',AsaController.time_zones_details.end_hour, ':',AsaController.time_zones_details.end_minute) AS endTime,
							CURRENT_TIMESTAMP() AS date,
							CASE
									WHEN DAYOFWEEK(CURDATE()) < 7 THEN DAYOFWEEK(CURDATE())+1
									WHEN DAYOFWEEK(CURDATE()) = 7 THEN 1
							END AS currentDayOfweek ,
							AsaController.access_times_details.dayOfWeek,
							AsaController.tags.real_user_fr,
							AsaController.terminals.terminalId,
							AsaController.terminals.type
							FROM
							AsaController.tags
							INNER JOIN AsaController.personnel_access_groups ON AsaController.tags.real_user_fr = AsaController.personnel_access_groups.real_user_fr
							INNER JOIN AsaController.access_groups_details ON AsaController.access_groups_details.access_group_fr = AsaController.personnel_access_groups.access_group_fr
							INNER JOIN AsaController.access_times ON AsaController.access_groups_details.access_time_fr = AsaController.access_times.id
							INNER JOIN AsaController.access_times_details ON AsaController.access_times_details.access_time_fr = AsaController.access_times.id
							INNER JOIN AsaController.time_zones_details ON AsaController.time_zones_details.time_zone_fr = AsaController.access_times_details.time_zone_fr
							INNER JOIN AsaController.access_group_terminals ON AsaController.access_group_terminals.access_group_fr = AsaController.personnel_access_groups.access_group_fr
							INNER JOIN AsaController.terminals ON AsaController.access_group_terminals.terminal_fr = AsaController.terminals.id
							WHERE
							AsaController.tags.tagId = '5' AND
							AsaController.tags.mainItem = TagNumber AND
							AsaController.terminals.terminalId = TerminalId AND
							AsaController.terminals.type = 'UPass' AND
							AsaController.access_times_details.dayOfWeek = CASE
						  WHEN DAYOFWEEK(CURDATE()) < 7 THEN DAYOFWEEK(CURDATE())+1
              WHEN DAYOFWEEK(CURDATE()) = 7 THEN 1
							END AND
							AsaController.personnel_access_groups.archived is NULL AND
 							AsaController.terminals.archived is NULL AND
 							AsaController.tags.archived is NULL AND
							TIME(now()) >= TIME(CONCAT(AsaController.time_zones_details.start_hour, ':',AsaController.time_zones_details.start_minute , ':00')) 
							and
							TIME(now()) <= TIME(CONCAT(AsaController.time_zones_details.end_hour, ':',AsaController.time_zones_details.end_minute, ':00')) ;
-- 							CONCAT(CURDATE(),' ',AsaController.time_zones_details.start_hour, ':',AsaController.time_zones_details.start_minute) <= DATE_FORMAT(CURRENT_TIMESTAMP(), '%Y-%m-%d %k:%i') AND
-- 							CONCAT(CURDATE(),' ',AsaController.time_zones_details.end_hour, ':',AsaController.time_zones_details.end_minute) >=  DATE_FORMAT(CURRENT_TIMESTAMP(), '%Y-%m-%d %k:%i');
		END IF;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for sp_upass_status
-- ----------------------------
DROP PROCEDURE IF EXISTS `sp_upass_status`;
delimiter ;;
CREATE PROCEDURE `sp_upass_status`(IN TerminalId INT)
BEGIN 
		IF EXISTS(SELECT 
						 * 
						 FROM 
						 AsaController.serv_terminal_status 
						 WHERE 
						 AsaController.serv_terminal_status.terminalId = TerminalId
						 LIMIT 1
				)THEN UPDATE AsaController.serv_terminal_status 
										SET 
										updated_at = CURRENT_TIMESTAMP
							WHERE terminalId = TerminalId;
					ELSE
						INSERT INTO AsaController.serv_terminal_status (terminalId, created_at, updated_at)
						VALUES 
						(terminalId,CURRENT_TIMESTAMP, CURRENT_TIMESTAMP);
		END IF;
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
