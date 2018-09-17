-- --------------------------------------------------------
--
-- テーブルの構造 `D_TCUP_ATTENDEE`
--

CREATE TABLE IF NOT EXISTS `D_TCUP_ATTENDEE` (
  `tcup_id` int(10) unsigned NOT NULL COMMENT '大会ID',
  `tcup_member_id` int(10) unsigned NOT NULL COMMENT 'メンバーID',
  `tcup_result_rank` int(10) DEFAULT NULL COMMENT '結果順位',
  `attend_comment` varchar(256) DEFAULT NULL COMMENT '参加コメント',
  `update_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新日',
  `create_date` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT '作成日',
  PRIMARY KEY (`tcup_id`,`tcup_member_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='大会参加者管理';

-- --------------------------------------------------------

--
-- テーブルの構造 `D_TCUP_RESULT`
--

CREATE TABLE IF NOT EXISTS `D_TCUP_RESULT` (
  `tcup_id` int(10) unsigned NOT NULL COMMENT '大会ID',
  `tcup_member_id` int(10) unsigned NOT NULL COMMENT 'メンバーID',
  `battle_no` tinyint(1) unsigned NOT NULL COMMENT 'N回戦',
  `table_no` tinyint(1) unsigned NOT NULL COMMENT '卓番号',
  `result_point` float NOT NULL COMMENT '得点',
  `result_rank` tinyint(1) unsigned NOT NULL COMMENT '順位',
  `update_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新日',
  `create_date` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT '作成日',
  PRIMARY KEY (`tcup_id`,`tcup_member_id`,`battle_no`),
  KEY `tcup_id` (`tcup_id`,`battle_no`,`table_no`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='結果詳細';

-- --------------------------------------------------------

--
-- テーブルの構造 `D_TCUP_YAKUMAN_GETTER`
--

CREATE TABLE IF NOT EXISTS `D_TCUP_YAKUMAN_GETTER` (
  `tcup_yakuman_id` int(10) unsigned NOT NULL COMMENT '採用役満ID',
  `tcup_id` int(10) DEFAULT NULL COMMENT '大会ID',
  `tcup_member_id` int(10) unsigned NOT NULL COMMENT 'メンバーID',
  `create_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '作成日',
  KEY `tcup_yakuman_id` (`tcup_yakuman_id`),
  KEY `tcup_id` (`tcup_id`),
  KEY `tcup_member_id` (`tcup_member_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='役満取得者管理';

-- --------------------------------------------------------

--
-- テーブルの構造 `D_TOPEN_ATTENDEE`
--

CREATE TABLE IF NOT EXISTS `D_TOPEN_ATTENDEE` (
  `topen_id` int(10) unsigned NOT NULL COMMENT 'オープン戦ID',
  `tcup_member_id` int(10) unsigned NOT NULL COMMENT 'メンバーID',
  `topen_result_rank` int(10) DEFAULT NULL COMMENT '結果順位',
  `update_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新日',
  `create_date` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT '作成日',
  PRIMARY KEY (`topen_id`,`tcup_member_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='オープン戦参加者管理';

-- --------------------------------------------------------

--
-- テーブルの構造 `D_TOPEN_RESULT`
--

CREATE TABLE IF NOT EXISTS `D_TOPEN_RESULT` (
  `topen_id` int(10) unsigned NOT NULL COMMENT 'オープン戦ID',
  `tcup_member_id` int(10) unsigned NOT NULL COMMENT 'メンバーID',
  `battle_no` tinyint(1) unsigned NOT NULL COMMENT 'N回戦',
  `table_no` tinyint(1) unsigned NOT NULL COMMENT '卓番号',
  `result_point` float NOT NULL COMMENT '得点',
  `result_rank` tinyint(1) unsigned NOT NULL COMMENT '順位',
  `fault_count` tinyint(1) unsigned NOT NULL COMMENT 'チョンボ回数',
  `is_yakitori_get` tinyint(1) unsigned NOT NULL COMMENT 'ヤキトリか（0:いいえ、1:はい）',
  `update_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新日',
  `create_date` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT '作成日',
  PRIMARY KEY (`topen_id`,`tcup_member_id`,`battle_no`),
  KEY `topen_id` (`topen_id`,`battle_no`,`table_no`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='オープン戦結果詳細';

-- --------------------------------------------------------

--
-- テーブルの構造 `D_TOPEN_YAKUMAN_GETTER`
--

CREATE TABLE IF NOT EXISTS `D_TOPEN_YAKUMAN_GETTER` (
  `tcup_yakuman_id` int(10) unsigned NOT NULL COMMENT '採用役満ID',
  `topen_id` int(10) DEFAULT NULL COMMENT '大会ID',
  `tcup_member_id` int(10) unsigned NOT NULL COMMENT 'メンバーID',
  `create_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '作成日',
  KEY `tcup_yakuman_id` (`tcup_yakuman_id`),
  KEY `topen_id` (`topen_id`),
  KEY `tcup_member_id` (`tcup_member_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='オープン戦役満取得者管理';

-- --------------------------------------------------------

--
-- テーブルの構造 `M_TCUP`
--

CREATE TABLE IF NOT EXISTS `M_TCUP` (
  `tcup_id` int(10) unsigned NOT NULL COMMENT '大会ID',
  `tcup_type` tinyint(1) unsigned NOT NULL COMMENT '大会タイプ(1:通常,2:最強位)',
  `tcup_serial_id` int(10) unsigned NOT NULL COMMENT '大会種別通し番号',
  `tcup_name` varchar(32) DEFAULT NULL COMMENT '大会名称',
  `open_date` date NOT NULL COMMENT '開催日',
  `create_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '作成日',
  PRIMARY KEY (`tcup_id`),
  KEY `tcup_type` (`tcup_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='大会マスター';

-- --------------------------------------------------------

--
-- テーブルの構造 `M_TCUP_MEMBER`
--

CREATE TABLE IF NOT EXISTS `M_TCUP_MEMBER` (
  `tcup_member_id` int(10) unsigned NOT NULL COMMENT 'メンバーID',
  `tcup_member_first_name` varchar(32) DEFAULT NULL COMMENT '名字',
  `tcup_member_last_name` varchar(32) DEFAULT NULL COMMENT '名前',
  `tcup_member_nickname` varchar(32) DEFAULT NULL COMMENT 'あだ名',
  `visible_name` varchar(32) DEFAULT NULL COMMENT '表示名',
  `tcup_member_img` varchar(32) NOT NULL COMMENT '使用イメージファイル名',
  `create_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '作成日',
  PRIMARY KEY (`tcup_member_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='大会参加メンバー';

-- --------------------------------------------------------

--
-- テーブルの構造 `M_TCUP_YAKUMAN`
--

CREATE TABLE IF NOT EXISTS `M_TCUP_YAKUMAN` (
  `tcup_yakuman_id` int(10) unsigned NOT NULL COMMENT '採用役満ID',
  `tcup_yakuman_name` varchar(32) DEFAULT NULL COMMENT '採用役満名前',
  `create_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '作成日',
  PRIMARY KEY (`tcup_yakuman_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='採用役満管理';

-- --------------------------------------------------------

--
-- テーブルの構造 `M_TOPEN`
--

CREATE TABLE IF NOT EXISTS `M_TOPEN` (
  `topen_id` int(10) unsigned NOT NULL COMMENT 'オープン戦ID',
  `topen_place_name` varchar(16) DEFAULT NULL COMMENT '場所名称',
  `is_red` tinyint(1) unsigned NOT NULL COMMENT '赤アリか（0:なし、1:あり）',
  `is_yakitori` tinyint(1) unsigned NOT NULL COMMENT 'ヤキトリか（0:なし、1:あり）',
  `is_rtd` tinyint(4) NOT NULL DEFAULT '0' COMMENT 'RTD模擬か(0:なし、1:あり)',
  `open_date` date NOT NULL COMMENT '開催日',
  `create_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '作成日',
  PRIMARY KEY (`topen_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='オープン戦マスター';
