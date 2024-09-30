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

 Date: 27/10/2019 21:58:06
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
-- Records of access_group_terminals
-- ----------------------------
INSERT INTO `access_group_terminals` VALUES (23, 2, 3, '2019-09-23 10:18:36', '2019-09-23 10:18:36');
INSERT INTO `access_group_terminals` VALUES (29, 8, 6, '2019-09-23 13:04:30', '2019-09-23 13:04:30');
INSERT INTO `access_group_terminals` VALUES (33, 8, 3, '2019-09-24 09:44:31', '2019-09-24 09:44:31');
INSERT INTO `access_group_terminals` VALUES (35, 9, 6, '2019-09-24 10:18:30', '2019-09-24 10:18:30');
INSERT INTO `access_group_terminals` VALUES (36, 9, 3, '2019-09-26 11:34:17', '2019-09-26 11:34:17');
INSERT INTO `access_group_terminals` VALUES (37, 2, 10, '2019-10-21 16:59:27', '2019-10-21 16:59:27');
INSERT INTO `access_group_terminals` VALUES (39, 11, 3, '2019-10-23 14:24:40', '2019-10-23 14:24:40');
INSERT INTO `access_group_terminals` VALUES (40, 8, 10, '2019-10-23 15:39:35', '2019-10-23 15:39:35');
INSERT INTO `access_group_terminals` VALUES (41, 12, 10, '2019-10-23 17:55:02', '2019-10-23 17:55:02');
INSERT INTO `access_group_terminals` VALUES (42, 13, 11, '2019-10-23 17:57:09', '2019-10-23 17:57:09');
INSERT INTO `access_group_terminals` VALUES (43, 12, 11, '2019-10-25 20:03:17', '2019-10-25 20:03:17');

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
-- Records of access_groups_details
-- ----------------------------
INSERT INTO `access_groups_details` VALUES (71, 9, 5, '2019-09-26 14:31:54', '2019-09-26 14:31:54');
INSERT INTO `access_groups_details` VALUES (73, 2, 1, '2019-10-22 10:42:38', '2019-10-22 10:42:38');
INSERT INTO `access_groups_details` VALUES (74, 2, 9, '2019-10-22 10:42:38', '2019-10-22 10:42:38');
INSERT INTO `access_groups_details` VALUES (80, 11, 5, '2019-10-23 14:40:27', '2019-10-23 14:40:27');
INSERT INTO `access_groups_details` VALUES (81, 8, 1, '2019-10-23 15:39:34', '2019-10-23 15:39:34');
INSERT INTO `access_groups_details` VALUES (83, 13, 11, '2019-10-23 17:57:09', '2019-10-23 17:57:09');
INSERT INTO `access_groups_details` VALUES (87, 12, 10, '2019-10-26 03:28:52', '2019-10-26 03:28:52');

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
-- Records of access_times
-- ----------------------------
INSERT INTO `access_times` VALUES (1, 'دسترسی کاربران', 6, '2019-09-02 17:52:04', '2019-09-02 18:19:16', NULL, NULL);
INSERT INTO `access_times` VALUES (5, 'زمان دسترسی سه شنبه', 6, '2019-09-24 10:18:04', '2019-09-24 19:00:52', NULL, NULL);
INSERT INTO `access_times` VALUES (9, 'ttttt', 10, '2019-10-21 17:18:44', '2019-10-22 09:24:24', NULL, NULL);
INSERT INTO `access_times` VALUES (10, 'دسترسی یوپس ۳', 11, '2019-10-23 17:32:05', '2019-10-23 17:33:37', NULL, NULL);
INSERT INTO `access_times` VALUES (11, 'دسترسی یوپس ۴', NULL, '2019-10-23 17:32:58', '2019-10-23 17:40:08', NULL, NULL);

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
-- Records of access_times_details
-- ----------------------------
INSERT INTO `access_times_details` VALUES (60, 1, '0', 16, '2019-09-23 17:36:18', '2019-09-23 17:36:18');
INSERT INTO `access_times_details` VALUES (61, 1, '1', 13, '2019-09-23 17:36:18', '2019-09-23 17:36:18');
INSERT INTO `access_times_details` VALUES (62, 1, '2', 13, '2019-09-23 17:36:18', '2019-09-23 17:36:18');
INSERT INTO `access_times_details` VALUES (63, 1, '3', 16, '2019-09-23 17:36:18', '2019-09-23 17:36:18');
INSERT INTO `access_times_details` VALUES (64, 1, '4', 16, '2019-09-23 17:36:19', '2019-09-23 17:36:19');
INSERT INTO `access_times_details` VALUES (65, 1, '5', 18, '2019-09-23 17:36:19', '2019-09-23 17:36:19');
INSERT INTO `access_times_details` VALUES (66, 1, '6', 18, '2019-09-23 17:36:19', '2019-09-23 17:36:19');
INSERT INTO `access_times_details` VALUES (67, 1, '7', 18, '2019-09-23 17:36:19', '2019-09-23 17:36:19');
INSERT INTO `access_times_details` VALUES (132, 5, '0', 20, '2019-09-26 10:52:57', '2019-09-26 10:52:57');
INSERT INTO `access_times_details` VALUES (133, 5, '1', 20, '2019-09-26 10:52:57', '2019-09-26 10:52:57');
INSERT INTO `access_times_details` VALUES (134, 5, '2', 20, '2019-09-26 10:52:57', '2019-09-26 10:52:57');
INSERT INTO `access_times_details` VALUES (135, 5, '3', 20, '2019-09-26 10:52:57', '2019-09-26 10:52:57');
INSERT INTO `access_times_details` VALUES (136, 5, '4', 20, '2019-09-26 10:52:57', '2019-09-26 10:52:57');
INSERT INTO `access_times_details` VALUES (137, 5, '5', 20, '2019-09-26 10:52:57', '2019-09-26 10:52:57');
INSERT INTO `access_times_details` VALUES (138, 5, '6', 23, '2019-09-26 10:52:57', '2019-09-26 10:52:57');
INSERT INTO `access_times_details` VALUES (139, 5, '7', 20, '2019-09-26 10:52:57', '2019-09-26 10:52:57');
INSERT INTO `access_times_details` VALUES (316, 11, '0', 28, '2019-10-23 17:56:25', '2019-10-23 17:56:25');
INSERT INTO `access_times_details` VALUES (317, 11, '1', 18, '2019-10-23 17:56:26', '2019-10-23 17:56:26');
INSERT INTO `access_times_details` VALUES (318, 11, '2', 18, '2019-10-23 17:56:26', '2019-10-23 17:56:26');
INSERT INTO `access_times_details` VALUES (319, 11, '3', 18, '2019-10-23 17:56:26', '2019-10-23 17:56:26');
INSERT INTO `access_times_details` VALUES (320, 11, '4', 18, '2019-10-23 17:56:26', '2019-10-23 17:56:26');
INSERT INTO `access_times_details` VALUES (321, 11, '5', 28, '2019-10-23 17:56:26', '2019-10-23 17:56:26');
INSERT INTO `access_times_details` VALUES (322, 11, '6', 28, '2019-10-23 17:56:26', '2019-10-23 17:56:26');
INSERT INTO `access_times_details` VALUES (323, 11, '7', 28, '2019-10-23 17:56:26', '2019-10-23 17:56:26');
INSERT INTO `access_times_details` VALUES (356, 9, '0', 18, '2019-10-24 09:27:54', '2019-10-24 09:27:54');
INSERT INTO `access_times_details` VALUES (357, 9, '1', 18, '2019-10-24 09:27:54', '2019-10-24 09:27:54');
INSERT INTO `access_times_details` VALUES (358, 9, '2', 18, '2019-10-24 09:27:55', '2019-10-24 09:27:55');
INSERT INTO `access_times_details` VALUES (359, 9, '3', 28, '2019-10-24 09:27:55', '2019-10-24 09:27:55');
INSERT INTO `access_times_details` VALUES (360, 9, '4', 18, '2019-10-24 09:27:55', '2019-10-24 09:27:55');
INSERT INTO `access_times_details` VALUES (361, 9, '5', 20, '2019-10-24 09:27:55', '2019-10-24 09:27:55');
INSERT INTO `access_times_details` VALUES (362, 9, '6', 28, '2019-10-24 09:27:55', '2019-10-24 09:27:55');
INSERT INTO `access_times_details` VALUES (363, 9, '7', 18, '2019-10-24 09:27:55', '2019-10-24 09:27:55');
INSERT INTO `access_times_details` VALUES (468, 10, '0', 29, '2019-10-27 20:33:39', '2019-10-27 20:33:39');
INSERT INTO `access_times_details` VALUES (469, 10, '1', 28, '2019-10-27 20:33:39', '2019-10-27 20:33:39');
INSERT INTO `access_times_details` VALUES (470, 10, '2', 28, '2019-10-27 20:33:39', '2019-10-27 20:33:39');
INSERT INTO `access_times_details` VALUES (471, 10, '3', 18, '2019-10-27 20:33:39', '2019-10-27 20:33:39');
INSERT INTO `access_times_details` VALUES (472, 10, '4', 18, '2019-10-27 20:33:39', '2019-10-27 20:33:39');
INSERT INTO `access_times_details` VALUES (473, 10, '5', 28, '2019-10-27 20:33:39', '2019-10-27 20:33:39');
INSERT INTO `access_times_details` VALUES (474, 10, '6', 28, '2019-10-27 20:33:39', '2019-10-27 20:33:39');
INSERT INTO `access_times_details` VALUES (475, 10, '7', 28, '2019-10-27 20:33:39', '2019-10-27 20:33:39');

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
-- Records of holidays_details
-- ----------------------------
INSERT INTO `holidays_details` VALUES (16, 7, '08-06', '2019-08-06 00:00:00', '2019-09-07 17:54:30', '2019-09-07 17:54:30', '08', '06');
INSERT INTO `holidays_details` VALUES (17, 6, '09-02', '2019-09-02 00:00:00', '2019-09-18 10:42:52', '2019-09-18 10:42:52', '09', '02');
INSERT INTO `holidays_details` VALUES (18, 6, '08-30', '2019-08-30 00:00:00', '2019-09-18 10:42:52', '2019-09-18 10:42:52', '08', '30');
INSERT INTO `holidays_details` VALUES (19, 6, '08-05', '2019-08-05 00:00:00', '2019-09-18 10:42:52', '2019-09-18 10:42:52', '08', '05');
INSERT INTO `holidays_details` VALUES (20, 6, '04-30', '2019-04-30 00:00:00', '2019-09-18 10:42:52', '2019-09-18 10:42:52', '04', '30');
INSERT INTO `holidays_details` VALUES (21, 6, '08-31', '2019-08-31 00:00:00', '2019-09-18 10:42:52', '2019-09-18 10:42:52', '08', '31');
INSERT INTO `holidays_details` VALUES (37, 8, '10-07', '2019-10-07 00:00:00', '2019-09-25 12:11:07', '2019-09-25 12:11:07', '10', '07');
INSERT INTO `holidays_details` VALUES (38, 8, '10-06', '2019-10-06 00:00:00', '2019-09-25 12:11:07', '2019-09-25 12:11:07', '10', '06');
INSERT INTO `holidays_details` VALUES (43, 10, '10-22', '2019-10-22 00:00:00', '2019-10-22 09:29:57', '2019-10-22 09:29:57', '10', '22');
INSERT INTO `holidays_details` VALUES (47, 11, '10-24', '2019-10-24 00:00:00', '2019-10-23 17:34:45', '2019-10-23 17:34:45', '10', '24');
INSERT INTO `holidays_details` VALUES (48, 13, '10-23', '2019-10-23 00:00:00', '2019-10-23 17:35:05', '2019-10-23 17:35:05', '10', '23');

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
-- Records of personnel_access_groups
-- ----------------------------
INSERT INTO `personnel_access_groups` VALUES (1, 2, 5, '111', '1', '1', NULL, NULL, '2019-09-03 14:47:33', '2019-09-03 14:48:15', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (2, 2, 5, 'در این تاریخ مجوز ...', '1', '1', 'به علت اخراج', NULL, '2019-09-03 15:09:01', '2019-09-03 15:29:08', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (3, 2, 5, 'به علت تردد', '1', '1', NULL, NULL, '2019-09-03 15:33:28', '2019-09-03 15:56:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (5, 2, 5, 'تردد', '1', '1', NULL, NULL, '2019-09-03 16:02:20', '2019-09-23 09:31:00', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (7, 2, 9, '....', '1', '1', NULL, NULL, '2019-09-16 16:53:40', '2019-09-21 12:45:06', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (8, 2, 8, NULL, '1', '1', NULL, NULL, '2019-09-17 14:38:35', '2019-09-21 12:45:35', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (11, 8, 9, NULL, '1', '1', NULL, NULL, '2019-09-21 12:45:06', '2019-09-21 12:46:24', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (12, 2, 9, '5544554', '1', '1', NULL, NULL, '2019-09-21 16:58:42', '2019-09-21 17:03:55', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (13, 2, 9, NULL, '1', '1', NULL, NULL, '2019-09-21 17:03:55', '2019-09-22 10:56:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (14, 2, 9, NULL, '1', '1', NULL, NULL, '2019-09-22 11:00:53', '2019-09-22 11:02:30', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (15, 8, 9, NULL, '1', '1', NULL, NULL, '2019-09-22 11:02:30', '2019-09-22 11:11:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (16, 2, 9, NULL, '1', '1', NULL, NULL, '2019-09-22 11:11:20', '2019-09-23 09:27:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (17, 2, 9, NULL, '1', '1', NULL, NULL, '2019-09-23 09:28:31', '2019-09-23 09:30:09', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (18, 8, 8, NULL, '1', '1', ' به علت تخصیص گروه دسترسی جدید ', NULL, '2019-09-23 09:30:34', '2019-10-13 08:51:00', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (19, 2, 13, NULL, '1', '1', NULL, NULL, '2019-09-23 10:17:22', '2019-09-23 10:19:42', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (20, 2, 13, NULL, '1', '1', NULL, NULL, '2019-09-23 10:19:42', '2019-09-23 10:32:35', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (21, 2, 14, NULL, '1', '1', NULL, NULL, '2019-09-23 10:29:05', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (22, 2, 16, NULL, '1', '1', NULL, NULL, '2019-09-23 10:30:36', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (23, 2, 13, NULL, '1', '1', NULL, NULL, '2019-09-23 10:32:35', '2019-09-24 18:55:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (27, 2, 15, NULL, '1', '1', NULL, NULL, '2019-09-23 17:43:34', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (28, 8, 21, NULL, '1', NULL, NULL, NULL, '2019-09-24 09:50:53', '2019-09-24 09:50:53', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (29, 2, 22, NULL, '1', NULL, NULL, NULL, '2019-09-24 09:55:04', '2019-09-24 09:55:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (30, 8, 23, NULL, '1', NULL, NULL, NULL, '2019-09-24 09:58:18', '2019-09-24 09:58:18', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (31, 9, 24, NULL, '1', '1', ' به علت تخصیص گروه دسترسی جدید ', NULL, '2019-09-24 10:20:31', '2019-10-15 08:29:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (32, 9, 25, NULL, '1', '1', NULL, NULL, '2019-09-24 10:23:00', '2019-09-29 09:40:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (33, 2, 13, NULL, '1', '1', NULL, NULL, '2019-09-24 18:55:26', '2019-09-24 18:55:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (34, 2, 13, NULL, '1', '1', NULL, NULL, '2019-09-24 18:55:26', '2019-09-24 19:02:34', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (37, 9, 26, NULL, '1', NULL, NULL, NULL, '2019-09-25 10:58:02', '2019-09-25 10:58:02', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (38, 9, 27, NULL, '1', NULL, NULL, NULL, '2019-09-25 11:11:20', '2019-09-25 11:11:20', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (39, 9, 18, NULL, '1', '1', ' به علت تخصیص گروه دسترسی جدید ', NULL, '2019-09-25 11:53:13', '2019-10-15 08:29:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (40, 8, 28, NULL, '1', '1', NULL, NULL, '2019-09-25 12:20:31', '2019-09-25 12:20:31', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (41, 9, 28, NULL, '1', '1', NULL, NULL, '2019-09-25 12:22:33', '2019-09-25 12:25:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (42, 2, 28, NULL, '1', NULL, NULL, NULL, '2019-09-25 12:25:48', '2019-09-25 12:25:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (43, 2, 29, NULL, '1', NULL, NULL, NULL, '2019-09-28 16:58:37', '2019-09-28 16:58:37', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (44, 2, 25, NULL, '1', '1', NULL, NULL, '2019-09-29 09:42:39', '2019-09-29 09:54:08', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (45, 2, 25, NULL, '1', '1', NULL, NULL, '2019-09-29 10:12:35', '2019-09-29 10:14:49', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (46, 2, 25, NULL, '1', '1', NULL, NULL, '2019-09-29 10:14:49', '2019-09-29 10:48:51', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (47, 2, 25, NULL, '1', '1', NULL, NULL, '2019-09-29 10:55:55', '2019-10-14 12:19:53', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (48, 2, 37, NULL, '1', NULL, NULL, NULL, '2019-09-29 16:43:40', '2019-09-29 16:43:40', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (49, 2, 9, NULL, '1', '1', ' به علت تخصیص گروه دسترسی جدید ', NULL, '2019-09-30 12:11:56', '2019-10-13 08:50:58', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (50, 2, 46, NULL, '1', NULL, NULL, NULL, '2019-10-02 16:20:46', '2019-10-02 16:20:46', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (54, 9, 19, NULL, '1', '1', NULL, NULL, '2019-10-13 08:51:02', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (55, 9, 44, NULL, '1', NULL, NULL, NULL, '2019-10-13 08:51:03', '2019-10-13 08:51:03', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (56, 2, 9, NULL, '1', '1', NULL, NULL, '2019-10-14 08:37:52', '2019-10-14 12:30:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (57, 2, 8, NULL, '1', '1', ' به علت تخصیص گروه دسترسی جدید ', NULL, '2019-10-14 08:37:52', '2019-10-16 08:51:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (58, 8, 25, NULL, '1', NULL, NULL, NULL, '2019-10-14 12:19:54', '2019-10-14 12:19:54', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (59, 8, 9, NULL, '1', '1', ' به علت تخصیص گروه دسترسی جدید ', NULL, '2019-10-14 12:31:14', '2019-10-16 08:51:42', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (60, 2, 13, NULL, '1', '1', ' به علت تخصیص گروه دسترسی جدید ', NULL, '2019-10-15 08:29:35', '2019-10-15 08:30:58', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (61, 2, 1758, NULL, '1', '1', ' به علت تخصیص گروه دسترسی جدید ', NULL, '2019-10-15 08:29:35', '2019-10-15 08:30:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (62, 2, 24, NULL, '1', '1', ' به علت تخصیص گروه دسترسی جدید ', NULL, '2019-10-15 08:29:36', '2019-10-15 08:30:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (64, 2, 13, NULL, '1', '1', NULL, NULL, '2019-10-15 08:30:58', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (65, 2, 1758, NULL, '1', NULL, NULL, NULL, '2019-10-15 08:30:59', '2019-10-15 08:30:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (66, 2, 24, NULL, '1', NULL, NULL, NULL, '2019-10-15 08:30:59', '2019-10-15 08:30:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (68, 2, 1757, NULL, '1', NULL, NULL, NULL, '2019-10-16 08:51:41', '2019-10-16 08:51:41', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (69, 2, 9, NULL, '1', '1', NULL, NULL, '2019-10-16 08:51:42', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (70, 2, 1756, NULL, '1', NULL, NULL, NULL, '2019-10-16 08:51:43', '2019-10-16 08:51:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (71, 2, 8, NULL, '1', '1', NULL, NULL, '2019-10-16 08:51:44', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (72, 2, 5, NULL, '1', '1', NULL, NULL, '2019-10-16 08:51:45', '2019-10-22 16:30:09', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (73, 8, 1767, '', '1', '1', NULL, NULL, '2019-10-20 08:51:34', '2019-10-20 08:51:34', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (84, 9, 23, NULL, '1', NULL, NULL, NULL, '2019-10-22 15:07:48', '2019-10-22 15:07:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (85, 9, 24, NULL, '1', NULL, NULL, NULL, '2019-10-22 15:08:03', '2019-10-22 15:08:03', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (100, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 15:18:44', '2019-10-22 16:30:09', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (101, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 15:18:44', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (102, 9, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 15:18:44', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (103, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 15:18:44', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (104, 8, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 15:18:44', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (105, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 15:18:44', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (106, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 15:18:44', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (107, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 15:18:44', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (108, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 15:18:44', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (109, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 15:18:44', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (110, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 15:18:44', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (111, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 16:30:09', '2019-10-22 16:31:29', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (112, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 16:31:29', '2019-10-22 16:39:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (113, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 16:31:29', '2019-10-22 16:39:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (114, 9, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 16:31:29', '2019-10-22 16:39:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (115, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 16:31:29', '2019-10-22 16:39:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (116, 8, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 16:31:29', '2019-10-22 16:39:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (117, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 16:31:29', '2019-10-22 16:39:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (118, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 16:31:29', '2019-10-22 16:39:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (119, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 16:31:29', '2019-10-22 16:39:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (120, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 16:31:29', '2019-10-22 16:39:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (121, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 16:31:29', '2019-10-22 16:39:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (122, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 16:31:29', '2019-10-22 16:39:48', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (123, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 16:39:48', '2019-10-22 16:54:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (124, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 16:39:48', '2019-10-22 16:54:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (125, 9, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 16:39:48', '2019-10-22 16:54:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (126, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 16:39:48', '2019-10-22 16:54:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (127, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 16:39:48', '2019-10-22 16:54:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (128, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 16:39:48', '2019-10-22 16:54:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (129, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 16:39:48', '2019-10-22 16:54:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (130, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 16:39:48', '2019-10-22 16:54:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (131, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 16:39:48', '2019-10-22 16:54:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (132, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 16:39:48', '2019-10-22 16:54:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (133, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 16:39:48', '2019-10-22 16:54:26', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (134, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 16:54:26', '2019-10-22 17:03:22', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (135, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 16:54:26', '2019-10-22 17:03:22', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (136, 9, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 16:54:26', '2019-10-22 17:03:22', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (137, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 16:54:26', '2019-10-22 17:03:22', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (138, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 16:54:26', '2019-10-22 17:03:22', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (139, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 16:54:26', '2019-10-22 17:03:22', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (140, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 16:54:26', '2019-10-22 17:03:22', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (141, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 16:54:26', '2019-10-22 17:03:22', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (142, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 16:54:26', '2019-10-22 17:03:22', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (143, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 16:54:26', '2019-10-22 17:03:22', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (144, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 16:54:26', '2019-10-22 17:03:22', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (145, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:04:28', '2019-10-22 17:06:54', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (146, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:04:28', '2019-10-22 17:06:54', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (147, 9, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:04:28', '2019-10-22 17:06:54', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (148, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:04:28', '2019-10-22 17:06:54', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (149, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:04:28', '2019-10-22 17:06:54', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (150, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:04:28', '2019-10-22 17:06:54', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (151, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:04:28', '2019-10-22 17:06:54', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (152, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:04:28', '2019-10-22 17:06:54', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (153, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:04:28', '2019-10-22 17:06:54', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (154, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:04:28', '2019-10-22 17:06:54', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (155, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:04:28', '2019-10-22 17:06:54', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (156, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:13:25', '2019-10-22 17:15:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (157, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:13:25', '2019-10-22 17:15:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (158, 9, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:13:25', '2019-10-22 17:15:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (159, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:13:25', '2019-10-22 17:15:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (160, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:13:25', '2019-10-22 17:15:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (161, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:13:25', '2019-10-22 17:15:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (162, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:13:25', '2019-10-22 17:15:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (163, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:13:25', '2019-10-22 17:15:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (164, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:13:25', '2019-10-22 17:15:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (165, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:13:25', '2019-10-22 17:15:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (166, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:13:25', '2019-10-22 17:15:19', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (167, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:15:19', '2019-10-22 17:17:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (168, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:15:19', '2019-10-22 17:17:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (169, 9, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:15:19', '2019-10-22 17:17:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (170, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:15:19', '2019-10-22 17:17:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (171, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:15:19', '2019-10-22 17:17:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (172, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:15:19', '2019-10-22 17:17:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (173, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:15:19', '2019-10-22 17:17:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (174, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:15:19', '2019-10-22 17:17:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (175, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:15:19', '2019-10-22 17:17:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (176, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:15:19', '2019-10-22 17:17:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (177, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:15:19', '2019-10-22 17:17:04', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (178, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:04', '2019-10-22 17:17:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (179, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:04', '2019-10-22 17:17:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (180, 9, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:04', '2019-10-22 17:17:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (181, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:04', '2019-10-22 17:17:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (182, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:04', '2019-10-22 17:17:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (183, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:04', '2019-10-22 17:17:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (184, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:04', '2019-10-22 17:17:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (185, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:04', '2019-10-22 17:17:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (186, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:04', '2019-10-22 17:17:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (187, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:04', '2019-10-22 17:17:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (188, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:04', '2019-10-22 17:17:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (189, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:44', '2019-10-22 17:18:20', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (190, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:44', '2019-10-22 17:18:20', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (191, 9, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:44', '2019-10-22 17:18:20', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (192, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:44', '2019-10-22 17:18:20', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (193, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:44', '2019-10-22 17:18:20', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (194, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:44', '2019-10-22 17:18:20', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (195, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:44', '2019-10-22 17:18:20', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (196, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:44', '2019-10-22 17:18:20', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (197, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:44', '2019-10-22 17:18:20', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (198, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:44', '2019-10-22 17:18:20', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (199, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:17:44', '2019-10-22 17:18:20', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (200, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:20', '2019-10-22 17:18:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (201, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:20', '2019-10-22 17:18:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (202, 8, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:20', '2019-10-22 17:18:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (203, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:20', '2019-10-22 17:18:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (204, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:20', '2019-10-22 17:18:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (205, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:20', '2019-10-22 17:18:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (206, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:20', '2019-10-22 17:18:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (207, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:20', '2019-10-22 17:18:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (208, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:20', '2019-10-22 17:18:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (209, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:20', '2019-10-22 17:18:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (210, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:20', '2019-10-22 17:18:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (211, 2, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:43', '2019-10-22 17:20:40', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (212, 2, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:43', '2019-10-22 17:20:40', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (213, 8, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:43', '2019-10-22 17:20:40', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (214, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:43', '2019-10-22 17:20:40', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (215, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:43', '2019-10-22 17:20:40', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (216, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:43', '2019-10-22 17:20:40', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (217, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:43', '2019-10-22 17:20:40', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (218, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:43', '2019-10-22 17:20:40', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (219, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:43', '2019-10-22 17:20:40', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (220, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:43', '2019-10-22 17:20:40', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (221, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:18:43', '2019-10-22 17:20:40', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (222, 2, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:20:40', '2019-10-22 17:22:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (223, 2, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:20:40', '2019-10-22 17:22:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (224, 8, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:20:40', '2019-10-22 17:22:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (225, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:20:40', '2019-10-22 17:22:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (226, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:20:40', '2019-10-22 17:22:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (227, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:20:40', '2019-10-22 17:22:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (228, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:20:40', '2019-10-22 17:22:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (229, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:20:40', '2019-10-22 17:22:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (230, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:20:40', '2019-10-22 17:22:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (231, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:20:40', '2019-10-22 17:22:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (232, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:20:40', '2019-10-22 17:22:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (233, 2, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:22:44', '2019-10-22 17:23:17', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (234, 2, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:22:44', '2019-10-22 17:23:17', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (235, 8, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:22:44', '2019-10-22 17:23:17', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (236, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:22:44', '2019-10-22 17:23:17', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (237, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:22:44', '2019-10-22 17:23:17', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (238, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:22:44', '2019-10-22 17:23:17', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (239, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:22:44', '2019-10-22 17:23:17', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (240, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:22:44', '2019-10-22 17:23:17', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (241, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:22:44', '2019-10-22 17:23:17', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (242, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:22:44', '2019-10-22 17:23:17', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (243, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:22:44', '2019-10-22 17:23:17', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (244, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:17', '2019-10-22 17:23:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (245, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:17', '2019-10-22 17:23:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (246, 8, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:17', '2019-10-22 17:23:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (247, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:17', '2019-10-22 17:23:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (248, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:17', '2019-10-22 17:23:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (249, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:17', '2019-10-22 17:23:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (250, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:17', '2019-10-22 17:23:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (251, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:17', '2019-10-22 17:23:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (252, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:17', '2019-10-22 17:23:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (253, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:17', '2019-10-22 17:23:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (254, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:17', '2019-10-22 17:23:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (255, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:36', '2019-10-22 17:23:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (256, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:36', '2019-10-22 17:23:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (257, 8, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:36', '2019-10-22 17:23:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (258, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:36', '2019-10-22 17:23:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (259, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:36', '2019-10-22 17:23:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (260, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:36', '2019-10-22 17:23:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (261, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:36', '2019-10-22 17:23:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (262, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:36', '2019-10-22 17:23:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (263, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:36', '2019-10-22 17:23:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (264, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:36', '2019-10-22 17:23:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (265, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:36', '2019-10-22 17:23:59', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (266, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:59', '2019-10-22 17:24:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (267, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:59', '2019-10-22 17:24:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (268, 8, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:59', '2019-10-22 17:24:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (269, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:59', '2019-10-22 17:24:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (270, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:59', '2019-10-22 17:24:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (271, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:59', '2019-10-22 17:24:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (272, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:59', '2019-10-22 17:24:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (273, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:59', '2019-10-22 17:24:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (274, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:59', '2019-10-22 17:24:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (275, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:59', '2019-10-22 17:24:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (276, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:23:59', '2019-10-22 17:24:36', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (277, 9, 5, NULL, '1', '1', NULL, NULL, '2019-10-22 17:24:36', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (278, 9, 8, NULL, '1', '1', NULL, NULL, '2019-10-22 17:24:36', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (279, 8, 9, NULL, '1', '1', NULL, NULL, '2019-10-22 17:24:36', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (280, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:24:36', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (281, 2, 14, NULL, '1', '1', NULL, NULL, '2019-10-22 17:24:36', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (282, 8, 15, NULL, '1', '1', NULL, NULL, '2019-10-22 17:24:36', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (283, 8, 16, NULL, '1', '1', NULL, NULL, '2019-10-22 17:24:36', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (284, 2, 17, NULL, '1', '1', NULL, NULL, '2019-10-22 17:24:36', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (285, 2, 18, NULL, '1', '1', NULL, NULL, '2019-10-22 17:24:36', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (286, 2, 19, NULL, '1', '1', NULL, NULL, '2019-10-22 17:24:36', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (287, 9, 1767, NULL, '1', '1', NULL, NULL, '2019-10-22 17:24:36', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (288, 2, 5, NULL, '1', NULL, NULL, NULL, '2019-10-22 17:25:07', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (289, 2, 8, NULL, '1', NULL, NULL, NULL, '2019-10-22 17:25:07', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (290, 8, 9, NULL, '1', NULL, NULL, NULL, '2019-10-22 17:25:07', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (291, 9, 13, NULL, '1', '1', NULL, NULL, '2019-10-22 17:25:07', '2019-10-24 13:27:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (292, 2, 14, NULL, '1', NULL, NULL, NULL, '2019-10-22 17:25:07', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (293, 8, 15, NULL, '1', NULL, NULL, NULL, '2019-10-22 17:25:07', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (294, 8, 16, NULL, '1', NULL, NULL, NULL, '2019-10-22 17:25:07', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (295, 2, 17, NULL, '1', NULL, NULL, NULL, '2019-10-22 17:25:07', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (296, 2, 18, NULL, '1', NULL, NULL, NULL, '2019-10-22 17:25:07', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (297, 2, 19, NULL, '1', NULL, NULL, NULL, '2019-10-22 17:25:07', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (298, 9, 1767, NULL, '1', NULL, NULL, NULL, '2019-10-22 17:25:07', '2019-10-22 17:25:07', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (299, 12, 1765, NULL, '1', '1', NULL, NULL, '2019-10-23 18:01:34', '2019-10-26 05:23:16', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (300, 13, 13, NULL, '1', NULL, NULL, NULL, '2019-10-24 13:27:44', '2019-10-24 13:27:44', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (301, 2, 1765, NULL, '1', '1', NULL, NULL, '2019-10-26 05:23:16', '2019-10-26 05:27:43', NULL, NULL);
INSERT INTO `personnel_access_groups` VALUES (302, 12, 1765, NULL, '1', NULL, NULL, NULL, '2019-10-26 05:27:43', '2019-10-26 05:27:43', NULL, NULL);

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
-- Records of serv_terminal_status
-- ----------------------------
INSERT INTO `serv_terminal_status` VALUES (65931, 1, 0, 2, 0, 0, 0, '2019-09-28 13:20:24', '2019-10-27 21:13:15');
INSERT INTO `serv_terminal_status` VALUES (65932, 2, 0, 2, 1, 0, 0, '2019-09-28 13:20:27', '2019-10-27 21:13:15');
INSERT INTO `serv_terminal_status` VALUES (65934, 3, NULL, NULL, NULL, NULL, NULL, '2019-10-25 19:46:48', '2019-10-27 21:13:15');
INSERT INTO `serv_terminal_status` VALUES (65935, 4, NULL, NULL, NULL, NULL, NULL, '2019-10-25 19:46:48', '2019-10-27 21:13:15');

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
-- Records of tags
-- ----------------------------
INSERT INTO `tags` VALUES (1, 'پلاک', '4', ',,الف,', 'پرشیا', 1, 'سفید', 1, NULL, NULL, NULL, NULL, 5, '0', '1', '1', '21', '2019-09-01 10:51:44', '0', '0', NULL, '2019-09-01 10:46:21', '2019-09-01 10:51:44', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (2, 'پلاک', '4', '88,968,الف,22', 'مازراتی', 3, 'رزگلد', 3, NULL, NULL, NULL, NULL, 5, '0', '1', '1', '22', '2019-09-03 16:33:11', '0', '0', NULL, '2019-09-01 10:52:20', '2019-09-03 16:33:11', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (3, 'پلاک', '4', '88,986,الف,22', 'مازراتی', NULL, 'رزگلد', NULL, NULL, NULL, NULL, NULL, 5, '0', '1', '1', NULL, '2019-09-22 10:34:20', '0', '0', NULL, '2019-09-01 10:53:00', '2019-09-22 10:34:21', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (4, 'بارکد', '1', '8888', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '0', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-03 16:46:32', '2019-09-03 17:43:43', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (5, 'کارت موقت', '2', '999', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '0', '1', '1', NULL, '2019-09-03 18:04:44', '0', '0', NULL, '2019-09-03 16:46:32', '2019-09-03 18:04:44', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (6, 'کارت دائم', '3', '6000', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '0', '1', '1', NULL, '2019-09-03 17:59:03', '0', '0', NULL, '2019-09-03 16:46:33', '2019-09-03 17:59:03', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (7, 'پلاک', '4', '22,125,الف,33', 'مازراتی', NULL, 'طوسی', NULL, NULL, NULL, NULL, NULL, 8, '1', '1', '1', NULL, '2019-09-03 17:58:06', '0', '0', NULL, '2019-09-03 16:46:33', '2019-09-03 17:58:06', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (8, 'تگ', '5', '8888', 'مازراتی', 3, 'طوسی', 4, NULL, NULL, NULL, NULL, 8, '1', '1', '1', NULL, '2019-09-03 17:58:06', '0', '0', NULL, '2019-09-03 17:43:43', '2019-09-03 17:58:06', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (9, 'تگ', '5', '968', 'مازراتی', NULL, 'طوسی', NULL, NULL, NULL, NULL, NULL, 8, '1', '1', '1', '22,125,الف,33', '2019-09-03 18:06:20', '0', '0', NULL, '2019-09-03 17:48:01', '2019-09-03 18:06:20', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (10, 'بارکد', '1', '888', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '1', '1', '1', NULL, '2019-09-03 18:06:48', '0', '0', NULL, '2019-09-03 17:57:26', '2019-09-03 18:06:48', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (11, 'کارت دائم', '3', '855', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '1', '1', '1', NULL, '2019-09-03 18:04:45', '0', '0', NULL, '2019-09-03 18:04:43', '2019-09-03 18:04:45', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (12, 'کارت دائم', '3', '555', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '1', '1', '1', NULL, '2019-09-03 18:07:19', '0', '0', NULL, '2019-09-03 18:06:48', '2019-09-03 18:07:19', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (13, 'پلاک', '4', '22,123,الف,22', 'پراید', NULL, 'سفید', NULL, NULL, NULL, NULL, NULL, 8, '1', NULL, '1', '22,123,الف,22', NULL, '0', '0', NULL, '2019-09-03 18:08:09', '2019-09-03 18:08:09', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (14, 'تگ', '5', '8555', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '1', '1', '1', ',,الف,', '2019-09-04 10:09:02', '0', '0', NULL, '2019-09-04 10:04:56', '2019-09-04 10:09:02', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (15, 'تگ', '5', '1236', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '1', '1', '1', ',,الف,', '2019-09-04 10:09:02', '0', '0', NULL, '2019-09-04 10:08:25', '2019-09-04 10:09:02', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (16, 'تگ', '5', '8555', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '1', '1', '1', ',,الف,', '2019-09-04 10:09:36', '0', '0', NULL, '2019-09-04 10:09:03', '2019-09-04 10:09:36', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (17, 'تگ', '5', '8555', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '1', '1', '1', ',,الف,', '2019-09-04 10:14:54', '0', '0', NULL, '2019-09-04 10:10:01', '2019-09-04 10:14:54', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (18, 'تگ', '5', '8555', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '1', '1', '1', ',,الف,', '2019-09-04 10:15:56', '0', '0', NULL, '2019-09-04 10:15:28', '2019-09-04 10:15:56', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (19, 'تگ', '5', '8555', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '1', NULL, '1', ',,الف,', NULL, '0', '0', NULL, '2019-09-04 10:16:47', '2019-09-04 10:16:47', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (20, 'تگ', '5', '1285', 'پراید', NULL, 'مشکلی', NULL, NULL, NULL, NULL, NULL, 8, '1', NULL, '1', '12,222,معلولین,33', NULL, '0', '0', NULL, '2019-09-04 10:17:36', '2019-09-04 10:17:36', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (21, 'بارکد', '1', '444545', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 9, '1', '1', '1', NULL, '2019-09-22 10:53:27', '0', '0', NULL, '2019-09-16 16:53:39', '2019-09-22 10:53:28', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (22, 'کارت دائم', '3', '6CEA552D', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-17 15:10:09', '2019-09-17 15:10:09', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (23, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 8, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-17 15:10:09', '2019-09-17 15:10:09', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (30, 'کارت دائم', '3', '17055C0A', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 13, '1', '1', '1', NULL, '2019-09-22 12:34:36', '0', '0', NULL, '2019-09-18 11:27:16', '2019-09-22 12:34:37', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (31, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 13, '1', '2', '1', NULL, '2019-09-22 12:34:37', '0', '0', NULL, '2019-09-18 11:27:17', '2019-09-22 12:34:37', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (32, 'کارت دائم', '3', '555445', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 9, '1', '1', '1', NULL, '2019-09-21 14:33:03', '0', '0', NULL, '2019-09-21 12:51:06', '2019-09-21 14:33:04', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (33, 'کارت موقت', '2', '53636', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 9, '1', '1', '1', NULL, '2019-09-21 16:53:19', '0', '0', NULL, '2019-09-21 16:33:49', '2019-09-21 16:53:19', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (34, 'بارکد', '1', '52525', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 9, '1', '1', '1', NULL, '2019-09-21 16:57:41', '0', '0', NULL, '2019-09-21 16:56:42', '2019-09-21 16:57:41', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (35, 'کارت دائم', '3', 'B07D8D00', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 14, '1', '1', '1', NULL, '2019-09-29 09:51:16', '0', '0', NULL, '2019-09-22 12:07:47', '2019-09-29 09:51:17', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (36, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 14, '1', '1', '1', NULL, '2019-09-29 09:51:49', '0', '0', NULL, '2019-09-22 12:07:47', '2019-09-29 09:51:50', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (37, 'کارت دائم', '3', 'DCFD622D', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-22 12:10:02', '2019-09-22 12:10:02', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (38, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-22 12:10:02', '2019-09-22 12:10:02', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (39, 'کارت دائم', '3', '7C29632D', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 16, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-22 12:19:10', '2019-09-22 12:19:10', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (40, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 16, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-22 12:19:11', '2019-09-22 12:19:11', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (41, 'کارت دائم', '3', '2C25612D', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 17, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-22 12:27:18', '2019-09-22 12:27:18', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (42, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 17, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-22 12:27:19', '2019-09-22 12:27:19', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (43, 'کارت دائم', '3', 'F450C100', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 13, '1', '1', '1', NULL, '2019-09-25 10:18:34', '0', '0', NULL, '2019-09-22 12:38:12', '2019-09-25 10:18:34', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (44, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 13, '1', '1', '1', NULL, '2019-09-25 10:18:34', '0', '0', NULL, '2019-09-22 12:38:12', '2019-09-25 10:18:35', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (45, 'کارت دائم', '3', 'BC05622D', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 18, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-22 12:40:00', '2019-09-22 12:40:00', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (46, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 18, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-22 12:40:00', '2019-09-22 12:40:00', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (47, 'کارت دائم', '3', 'FCDF602D', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 19, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-22 12:47:32', '2019-09-22 12:47:32', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (48, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 19, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-22 12:47:33', '2019-09-22 12:47:33', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (49, 'کارت دائم', '3', 'BC26552D', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 21, '1', '1', '1', NULL, '2019-09-24 09:52:49', '0', '0', NULL, '2019-09-24 09:50:53', '2019-09-24 09:52:49', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (50, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 21, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-24 09:52:49', '2019-09-24 09:52:49', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (51, 'کارت دائم', '3', 'BC26552D', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 21, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-24 09:53:22', '2019-09-24 09:53:22', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (52, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 22, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-24 09:55:04', '2019-09-24 09:55:04', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (53, 'کارت دائم', '3', '17055C0A', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 22, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-24 09:55:04', '2019-09-24 09:55:04', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (54, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 23, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-24 09:58:18', '2019-09-24 09:58:18', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (55, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 24, '1', '1', '1', NULL, '2019-10-12 18:05:59', '0', '0', NULL, '2019-09-24 10:20:31', '2019-10-12 18:06:00', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (56, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '2', '1', NULL, '2019-09-24 13:37:32', '0', '0', NULL, '2019-09-24 10:23:00', '2019-09-24 13:37:33', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (57, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '2', '1', NULL, '2019-09-24 13:43:45', '0', '0', NULL, '2019-09-24 13:39:05', '2019-09-24 13:43:46', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (58, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '2', '1', NULL, '2019-09-24 13:49:12', '0', '0', NULL, '2019-09-24 13:47:58', '2019-09-24 13:49:12', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (59, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '2', '1', NULL, '2019-09-24 14:33:53', '0', '0', NULL, '2019-09-24 14:32:57', '2019-09-24 14:33:53', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (60, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '2', '1', NULL, '2019-09-24 14:41:44', '0', '0', NULL, '2019-09-24 14:40:36', '2019-09-24 14:41:44', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (61, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '2', '1', NULL, '2019-09-24 14:49:16', '0', '0', NULL, '2019-09-24 14:41:45', '2019-09-24 14:49:17', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (62, 'بارکد', '1', '63636', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '1', '1', NULL, '2019-09-30 10:03:04', '0', '0', NULL, '2019-09-24 14:50:45', '2019-09-30 10:03:05', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (63, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '2', '1', NULL, '2019-09-24 14:51:20', '0', '0', NULL, '2019-09-24 14:50:45', '2019-09-24 14:51:21', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (64, 'کارت دائم', '3', '696969', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '1', '1', NULL, '2019-09-29 09:45:16', '0', '0', NULL, '2019-09-24 14:50:46', '2019-09-29 09:45:17', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (65, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '1', '1', NULL, '2019-09-24 15:25:16', '0', '0', NULL, '2019-09-24 14:52:02', '2019-09-24 15:25:17', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (66, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '1', '1', NULL, '2019-09-29 09:41:18', '0', '0', NULL, '2019-09-24 15:25:17', '2019-09-29 09:41:18', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (67, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 13, '1', '1', '1', NULL, '2019-09-25 10:55:07', '0', '0', NULL, '2019-09-25 10:21:17', '2019-09-25 10:55:08', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (68, 'کارت دائم', '3', 'F450C100', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 13, '1', '1', '1', NULL, '2019-09-25 10:55:08', '0', '0', NULL, '2019-09-25 10:21:17', '2019-09-25 10:55:08', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (69, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 13, '1', '1', '1', NULL, '2019-09-25 15:43:48', '0', '0', NULL, '2019-09-25 10:55:08', '2019-09-25 15:43:48', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (70, 'کارت دائم', '3', 'F450C100', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 13, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-25 10:55:08', '2019-09-25 10:55:08', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (71, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 26, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-25 10:58:03', '2019-09-25 10:58:03', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (72, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 27, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-25 11:11:20', '2019-09-25 11:11:20', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (73, 'بارکد', '1', '7788787', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 28, '1', '1', '1', NULL, '2019-09-25 12:22:33', '0', '0', NULL, '2019-09-25 12:20:32', '2019-09-25 12:22:33', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (74, 'تگ', '5', '8899889', 'پراید', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 28, '1', NULL, '1', '22,123,د,42', NULL, '0', '0', NULL, '2019-09-25 12:21:32', '2019-09-25 12:21:32', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (75, 'کارت موقت', '2', '45454545', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 28, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-25 12:22:33', '2019-09-25 12:22:33', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (76, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 13, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-09-25 15:45:39', '2019-09-25 15:45:39', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (77, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 29, '1', '1', '1', NULL, '2019-09-28 17:12:43', '0', '0', NULL, '2019-09-28 16:58:38', '2019-09-28 17:12:43', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (78, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '1', '1', NULL, '2019-09-29 09:42:08', '0', '0', NULL, '2019-09-29 09:41:19', '2019-09-29 09:42:08', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (79, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '1', '1', NULL, '2019-09-29 09:44:40', '0', '0', NULL, '2019-09-29 09:44:07', '2019-09-29 09:44:41', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (80, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '1', '1', NULL, '2019-09-29 09:50:25', '0', '0', NULL, '2019-09-29 09:48:30', '2019-09-29 09:50:25', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (81, 'کارت دائم', '3', 'B07D8D00', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 14, '1', '1', '1', NULL, '2019-09-29 09:56:40', '0', '0', NULL, '2019-09-29 09:52:24', '2019-09-29 09:56:40', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (82, 'کارت دائم', '3', 'B07D8D00', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '1', '1', NULL, '2019-09-29 10:49:14', '0', '0', NULL, '2019-09-29 09:57:15', '2019-09-29 10:49:15', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '1');
INSERT INTO `tags` VALUES (83, 'تگ', '5', '52525', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 9, '1', NULL, '1', ',,الف,', NULL, '0', '0', NULL, '2019-09-30 09:45:08', '2019-09-30 09:45:08', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (84, 'تگ', '5', '44454as', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 46, '1', NULL, '1', ',,الف,', NULL, '0', '0', NULL, '2019-10-02 16:20:46', '2019-10-02 16:20:46', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (85, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', '1', '1', NULL, '2019-10-14 10:45:43', '0', '0', NULL, '2019-10-12 18:01:23', '2019-10-14 10:45:44', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (86, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 24, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-10-12 18:06:01', '2019-10-12 18:06:01', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (87, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 14, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-10-13 08:35:46', '2019-10-13 08:35:46', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (88, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 14, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-10-13 08:35:50', '2019-10-13 08:35:50', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (89, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 25, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-10-14 10:45:45', '2019-10-14 10:45:45', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (90, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 9, '1', '1', '1', NULL, '2019-10-14 12:28:38', '0', '0', NULL, '2019-10-14 12:23:10', '2019-10-14 12:28:39', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (91, 'اثر انگشت', '6', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 9, '1', NULL, '1', NULL, NULL, '0', '0', NULL, '2019-10-14 12:30:13', '2019-10-14 12:30:13', NULL, NULL, NULL, NULL, '0', '0', NULL, NULL, '0');
INSERT INTO `tags` VALUES (92, 'تگ', '5', '2037044E677A5F2D800000', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 1765, '1', '1', '1', ',,الف,', '2019-10-24 13:25:53', '0', '0', NULL, '2019-10-23 18:01:36', '2019-10-24 13:25:53', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (93, 'تگ', '5', '4E2037044E677A5F2D800000', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 1765, '1', '1', '1', ',,الف,', '2019-10-25 19:57:09', '0', '0', NULL, '2019-10-24 13:25:54', '2019-10-25 19:57:10', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (94, 'تگ', '5', '4E2024000002D23000000000', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 13, '1', NULL, '1', ',,الف,', NULL, '0', '0', NULL, '2019-10-24 13:27:44', '2019-10-24 13:27:44', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (95, 'تگ', '5', '4E2037044E677A5F2D800000', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 1765, '1', '1', '1', ',,الف,', '2019-10-26 03:18:44', '0', '0', NULL, '2019-10-25 19:58:25', '2019-10-26 03:18:44', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (96, 'تگ', '5', '4E2037044E677A5F2D800000', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 1765, '1', '1', '1', ',,الف,', '2019-10-26 03:22:34', '0', '0', NULL, '2019-10-26 03:20:10', '2019-10-26 03:22:34', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');
INSERT INTO `tags` VALUES (97, 'تگ', '5', '4E2037044E677A5F2D800000', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 1765, '1', NULL, '1', ',,الف,', NULL, '0', '0', NULL, '2019-10-26 03:24:34', '2019-10-26 03:24:34', NULL, NULL, NULL, NULL, '0', '0', '0', NULL, '0');

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
-- Records of terminals
-- ----------------------------
INSERT INTO `terminals` VALUES (3, 1, '1.2.152', 'ترمینال1', '2019-09-17 09:38:30', '2019-10-23 14:40:27', 'مرکزی', 'کارمندان', 'arrival', NULL, NULL, NULL, '2', '11', '11', '11', '11', 'Virdi');
INSERT INTO `terminals` VALUES (6, 2, '1.3.2.5', 'ترمینال2', '2019-09-17 14:55:28', '2019-10-23 14:00:39', 'مشاورین', 'شماره3', 'arrival', NULL, NULL, NULL, '2', '11', '11', '11', '11', 'Virdi');
INSERT INTO `terminals` VALUES (7, 7878, '2112', 'dfdf', '2019-09-26 14:35:13', '2019-09-26 14:43:57', '454', '454545', 'un_defined', NULL, NULL, '1', '3', NULL, NULL, NULL, NULL, 'Virdi');
INSERT INTO `terminals` VALUES (8, 6, '1.1.1.11', 'admin', '2019-09-26 14:45:57', '2019-09-26 14:46:20', 'sdsds', 'sdsd', 'un_defined', NULL, NULL, '1', '3', NULL, NULL, NULL, NULL, 'Virdi');
INSERT INTO `terminals` VALUES (9, 10, '1.1.1.11', 'ترمنیال10', '2019-09-28 13:10:25', '2019-09-28 13:10:25', 'مشاورین', '101', 'un_defined', NULL, NULL, NULL, '4', NULL, NULL, NULL, NULL, 'Virdi');
INSERT INTO `terminals` VALUES (10, 3, '192.168.1.90', 'ترمینال upass 3', '2019-10-21 16:59:01', '2019-10-27 20:47:39', '...', '....', 'un_defined', NULL, NULL, NULL, '2', '11', '10', '10', '10', 'UPass');
INSERT INTO `terminals` VALUES (11, 4, '192.168.1.90', 'ترمینال UPass 4', '2019-10-23 17:10:49', '2019-10-27 20:47:39', '...', '...', 'un_defined', NULL, NULL, NULL, '2', '11', '10', '10', '10', 'UPass');

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
-- Records of time_zones_details
-- ----------------------------
INSERT INTO `time_zones_details` VALUES (32, '2', '18', '00', '19', '00', 16, '2019-09-08 15:50:16', '2019-09-08 15:50:16');
INSERT INTO `time_zones_details` VALUES (33, '7', '06', '00', '12', '00', 16, '2019-09-08 15:50:16', '2019-09-08 15:50:16');
INSERT INTO `time_zones_details` VALUES (34, '1', '10', '00', '15', '00', 17, '2019-09-17 16:43:48', '2019-09-17 16:43:48');
INSERT INTO `time_zones_details` VALUES (35, '2', '13', '00', '16', '00', 17, '2019-09-17 16:43:48', '2019-09-17 16:43:48');
INSERT INTO `time_zones_details` VALUES (36, '6', '11', '00', '19', '00', 17, '2019-09-17 16:43:48', '2019-09-17 16:43:48');
INSERT INTO `time_zones_details` VALUES (64, '10', '16', '00', '24', '00', 13, '2019-09-18 10:13:13', '2019-09-28 17:03:41');
INSERT INTO `time_zones_details` VALUES (65, '6', '12', '00', '23', '00', 16, '2019-09-23 12:36:10', '2019-09-23 12:36:10');
INSERT INTO `time_zones_details` VALUES (66, '1', '00', '00', '24', '00', 18, '2019-09-23 17:24:06', '2019-09-23 17:24:08');
INSERT INTO `time_zones_details` VALUES (67, '1', '08', '00', '10', '00', 19, '2019-09-24 10:17:37', '2019-09-24 10:17:37');
INSERT INTO `time_zones_details` VALUES (68, '2', '13', '00', '18', '00', 19, '2019-09-24 10:17:37', '2019-09-24 13:14:29');
INSERT INTO `time_zones_details` VALUES (69, '1', '08', '00', '24', '00', 20, '2019-09-24 18:48:02', '2019-09-25 10:01:29');
INSERT INTO `time_zones_details` VALUES (79, '3', '16', '00', '24', '00', 22, '2019-09-25 12:18:24', '2019-09-25 12:18:24');
INSERT INTO `time_zones_details` VALUES (80, '3', '16', '00', '24', '00', 22, '2019-09-25 12:18:24', '2019-09-25 12:18:24');
INSERT INTO `time_zones_details` VALUES (81, '1', '11', '20', '24', '00', 23, '2019-09-26 10:52:38', '2019-09-26 11:26:54');
INSERT INTO `time_zones_details` VALUES (83, '1', '10', '00', '18', '00', 24, '2019-09-26 12:53:11', '2019-09-26 12:53:11');
INSERT INTO `time_zones_details` VALUES (87, '1', '00', '00', '13', '30', 28, '2019-10-23 17:29:32', '2019-10-27 20:47:39');
INSERT INTO `time_zones_details` VALUES (88, '1', '08', '00', '10', '00', 29, '2019-10-23 17:30:56', '2019-10-23 17:30:56');
INSERT INTO `time_zones_details` VALUES (89, '2', '20', '00', '24', '00', 29, '2019-10-23 17:30:56', '2019-10-23 17:30:56');
INSERT INTO `time_zones_details` VALUES (90, '5', '12', '00', '14', '00', 29, '2019-10-23 17:30:56', '2019-10-23 17:30:56');
INSERT INTO `time_zones_details` VALUES (91, '9', '16', '00', '18', '00', 29, '2019-10-23 17:30:57', '2019-10-23 17:30:57');

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
