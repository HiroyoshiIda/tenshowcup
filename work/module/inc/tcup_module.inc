<?php
// tcup_module.
// 天翔杯utility.

/**
 * 個人成績取得
 * 
 * @param	dbo	[Object]	DBObject.
 * @param	member_id	[int]	tcup_member_id.
 * @param	tcup_type	[int]	最強位か（1が通常2が最強位）.
 * @return 	row	[array]		結果セット(NULLで失敗).
 */
function Get_PersonnelResult($dbo, $member_id)
{
	$SQL =	"SELECT ".
		"	SUM(CASE WHEN result_rank = 1 THEN 1 ELSE 0 END) AS 1st_count".
		"	,SUM(CASE WHEN result_rank = 2 THEN 1 ELSE 0 END) AS 2nd_count".
		"	,SUM(CASE WHEN result_rank = 3 THEN 1 ELSE 0 END) AS 3rd_count".
		"	,SUM(CASE WHEN result_rank = 4 THEN 1 ELSE 0 END) AS 4th_count".
		"	,SUM(CASE WHEN battle_no <= 4 AND result_rank = 1 THEN 1 ELSE 0 END) AS pre_1st_count".
		"	,SUM(CASE WHEN battle_no <= 4 AND result_rank = 2 THEN 1 ELSE 0 END) AS pre_2nd_count".
		"	,SUM(CASE WHEN battle_no <= 4 AND result_rank = 3 THEN 1 ELSE 0 END) AS pre_3rd_count".
		"	,SUM(CASE WHEN battle_no <= 4 AND result_rank = 4 THEN 1 ELSE 0 END) AS pre_4th_count".
		"	,SUM(CASE WHEN battle_no > 4 AND table_no = 1 AND result_rank = 1 THEN 1 ELSE 0 END) AS winners_1st_count".
		"	,SUM(CASE WHEN battle_no > 4 AND table_no = 1 AND result_rank = 2 THEN 1 ELSE 0 END) AS winners_2nd_count".
		"	,SUM(CASE WHEN battle_no > 4 AND table_no = 1 AND result_rank = 3 THEN 1 ELSE 0 END) AS winners_3rd_count".
		"	,SUM(CASE WHEN battle_no > 4 AND table_no = 1 AND result_rank = 4 THEN 1 ELSE 0 END) AS winners_4th_count".
		"	,SUM(CASE WHEN battle_no > 4 AND table_no != 1 AND result_rank = 1 THEN 1 ELSE 0 END) AS losers_1st_count".
		"	,SUM(CASE WHEN battle_no > 4 AND table_no != 1 AND result_rank = 2 THEN 1 ELSE 0 END) AS losers_2nd_count".
		"	,SUM(CASE WHEN battle_no > 4 AND table_no != 1 AND result_rank = 3 THEN 1 ELSE 0 END) AS losers_3rd_count".
		"	,SUM(CASE WHEN battle_no > 4 AND table_no != 1 AND result_rank = 4 THEN 1 ELSE 0 END) AS losers_4th_count".
		"	,SUM(result_point) AS total_point".
		"	,AVG(result_point) AS average_point".
		"	,MAX(result_point) AS max_point".
		"	,MIN(result_point) AS min_point".
		" FROM ".
		"	D_TCUP_RESULT ".
		"	, M_TCUP ".
		" WHERE ".
		"	tcup_type = "._D_TCUP_TYPE_NORMAL.
		"	AND M_TCUP.tcup_id = D_TCUP_RESULT.tcup_id ".
		"	AND tcup_member_id = {$member_id} ";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	$row = $dbo->fetch_assoc();
	return $row;
}

/**
 * 最強位個人成績取得
 * 
 * @param	dbo	[Object]	DBObject.
 * @param	member_id	[int]	tcup_member_id.
 * @return 	row	[array]		結果セット(NULLで失敗).
 */
function Get_PersonnelSPResult($dbo, $member_id)
{
	$SQL =	"SELECT ".
		"	SUM(CASE WHEN result_rank = 1 THEN 1 ELSE 0 END) AS 1st_count".
		"	,SUM(CASE WHEN result_rank = 2 THEN 1 ELSE 0 END) AS 2nd_count".
		"	,SUM(CASE WHEN result_rank = 3 THEN 1 ELSE 0 END) AS 3rd_count".
		"	,SUM(CASE WHEN result_rank = 4 THEN 1 ELSE 0 END) AS 4th_count".
		"	,SUM(CASE WHEN battle_no <= 5 AND result_rank = 1 THEN 1 ELSE 0 END) AS pre_1st_count".
		"	,SUM(CASE WHEN battle_no <= 5 AND result_rank = 2 THEN 1 ELSE 0 END) AS pre_2nd_count".
		"	,SUM(CASE WHEN battle_no <= 5 AND result_rank = 3 THEN 1 ELSE 0 END) AS pre_3rd_count".
		"	,SUM(CASE WHEN battle_no <= 5 AND result_rank = 4 THEN 1 ELSE 0 END) AS pre_4th_count".
		"	,SUM(CASE WHEN battle_no > 5 AND table_no = 1 AND result_rank = 1 THEN 1 ELSE 0 END) AS winners_1st_count".
		"	,SUM(CASE WHEN battle_no > 5 AND table_no = 1 AND result_rank = 2 THEN 1 ELSE 0 END) AS winners_2nd_count".
		"	,SUM(CASE WHEN battle_no > 5 AND table_no = 1 AND result_rank = 3 THEN 1 ELSE 0 END) AS winners_3rd_count".
		"	,SUM(CASE WHEN battle_no > 5 AND table_no = 1 AND result_rank = 4 THEN 1 ELSE 0 END) AS winners_4th_count".
		"	,SUM(result_point) AS total_point".
		"	,AVG(result_point) AS average_point".
		"	,MAX(result_point) AS max_point".
		"	,MIN(result_point) AS min_point".
		" FROM ".
		"	D_TCUP_RESULT ".
		"	, M_TCUP ".
		" WHERE ".
		"	tcup_type = "._D_TCUP_TYPE_SPECIAL.
		"	AND M_TCUP.tcup_id = D_TCUP_RESULT.tcup_id ".
		"	AND tcup_member_id = {$member_id} ";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	$row = $dbo->fetch_assoc();
	return $row;
}

/**
 * 対人戦績
 * 
 * @param	dbo	[Object]	DBObject.
 * @param	member_id	[int]	tcup_member_id.
 * @param	tcup_type	[int]	最強位か（1が通常2が最強位）.
 * @return 	row	[array]		結果セット(NULLで失敗).
 */
function Get_PersonnelOPResult($dbo, $member_id, $tcup_type = 1)
{
	$SQL =	"SELECT ".
		"	A.tcup_member_id ".
		"	,COUNT(A.tcup_member_id) AS battle_count".
		"	,SUM(CASE WHEN A.result_point < 0 AND B.result_point > 0 THEN 1 ELSE 0 END) AS win_count".
		"	,SUM(CASE WHEN A.result_point > 0 AND B.result_point < 0 THEN 1 ELSE 0 END) AS lose_count".
		"	,SUM(CASE WHEN A.result_point < B.result_point THEN 1 ELSE -1 END) AS compatible_point".
		" FROM ".
		"	D_TCUP_RESULT A".
		"	,D_TCUP_RESULT B".
		"	,M_TCUP C".
		" WHERE ".
		"	C.tcup_type = {$tcup_type} ".
		"	AND C.tcup_id = A.tcup_id ".
		"	AND C.tcup_id = B.tcup_id ".
		"	AND A.tcup_id = B.tcup_id ".
		"	AND A.battle_no = B.battle_no ".
		"	AND A.table_no = B.table_no ".
		"	AND B.tcup_member_id = {$member_id} ".
		"	AND A.tcup_member_id != {$member_id} ".
		"GROUP BY ".
		"	A.tcup_member_id ".
		"ORDER BY ".
		"	battle_count DESC";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	$rows = $dbo->fetch_all();
	return $rows;
}

/**
 * メンバーリスト取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	tcup_type	[int]		最強位か（1が通常2が最強位）.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupMemberList($dbo, $tcup_type = 1)
{
	$SQL =	"SELECT ".
		"	A.*".
		"	,(CASE WHEN MAX(C.tcup_id) = MIN(C.tcup_id) THEN 1 ELSE 0 END) AS is_guest ".	// ゲストチェック.
		" FROM ".
		"	M_TCUP_MEMBER A".
		"	,M_TCUP B".
		"	,D_TCUP_ATTENDEE C".
		" WHERE ".
		"	B.tcup_type = {$tcup_type}".
		"	AND B.tcup_id = C.tcup_id".
		"	AND C.tcup_member_id = A.tcup_member_id".
		"	AND C.tcup_result_rank IS NOT NULL ".
		" GROUP BY ".
		"	tcup_member_id";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	while ($row = $dbo->fetch_assoc()) {
		$ret[$row['tcup_member_id']] = $row;
	}
	return $ret;
}

/**
 * 大会参加者リスト取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	tcup_id		[int]		開催大会ID.
 * @param	tcup_type	[int]		最強位か（1が通常2が最強位）.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupAttendeeList($dbo, $tcup_id, $tcup_type = 1)
{
	$SQL =	"SELECT ".
		"	*".
		" FROM ".
		"	M_TCUP_MEMBER A".
 		"	,(".Get_AttendCountSQL($tcup_id, $tcup_type).") attend ".
 		"	,(".Get_AchievementSQL($tcup_id).") achievement ".
		" WHERE ".
		"	A.tcup_member_id = attend.tcup_member_id".
		"	AND A.tcup_member_id = achievement.tcup_member_id";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	while ($row = $dbo->fetch_assoc()) {
		$ret[$row['tcup_member_id']] = $row;
	}
	arsort($ret);	// 逆順に.
	return $ret;
}

/**
 * 大会参加/実績データを個人を指定して取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	tcup_member_id	[int]		開催大会ID.
 * @param	tcup_type	[int]		最強位か（1が通常2が最強位）.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupAttendeeData($dbo, $tcup_member_id, $tcup_type = 1)
{
	$SQL =	"SELECT ".
		"	MAX(tcup_id) AS tcup_id".
		" FROM ".
		"	M_TCUP";
//		" WHERE ".
//		"	tcup_type = {$tcup_type}";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	$max_row = $dbo->fetch_assoc();
	$tcup_id = ($max_row['tcup_id'] + 1);
	
	$SQL =	"SELECT ".
		"	*".
		" FROM ".
		"	(".Get_AchievementSQL($tcup_id, 0).") achievement ".
		"	INNER JOIN M_TCUP_MEMBER A ON achievement.tcup_member_id = A.tcup_member_id".
		"	INNER JOIN ".
		"	(".
		"		SELECT".
		"			tcup_member_id".
		"			, COUNT(tcup_id) AS attend_count".
		"		FROM ".
		"			D_TCUP_ATTENDEE ".
		"		WHERE ".
		"			tcup_member_id = {$tcup_member_id} ".
		"			AND tcup_result_rank > 0 ".
		"			AND tcup_id IN ( ".
		"				SELECT ".
		"					tcup_id ".
		"				FROM ".
		"					M_TCUP ".
		"				WHERE ".
		"					tcup_type = {$tcup_type} ".
		"				)".
		"	) B ON A.tcup_member_id = B.tcup_member_id".
		" WHERE ".
		"	A.tcup_member_id = {$tcup_member_id}".
		" GROUP BY ".
		"	A.tcup_member_id";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	$ret = $dbo->fetch_assoc();
	return $ret;
}

/**
 * 役満獲得状況取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupYakumanGetter($dbo)
{
	$SQL =	"SELECT ".
		"	A.*".
		"	,B.*".
		"	,C.*".
		" FROM ".
		"	D_TCUP_YAKUMAN_GETTER A".
		"	, M_TCUP_MEMBER B ".
		"	, M_TCUP_YAKUMAN C ".
		" WHERE ".
		"	A.tcup_yakuman_id = C.tcup_yakuman_id".
		"	AND A.tcup_member_id = B.tcup_member_id";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	// 獲得なしもありうる.
	if ($dbo->num_rows() < 1) {
		return array();
	}
	while ($row = $dbo->fetch_assoc()) {
		// 複数含まれるので大会IDでだけ仕切る.
		$ret[$row['tcup_id']][] = $row;
	}
	return $ret;
}

/**
 * メンバーリストプルダウン
 * 
 * @param	list	[array]		メンバーリスト.
 * @return 	ret	[str]		結果セット(NULLで失敗).
 */
function Show_MemberPulldownStr($list, $member_id = 1)
{
	$str = "";
	foreach ($list as $key => $data) {
		if ($key == $member_id) {
			$default = "selected";
		} else {
			$default = "";
		}
		
		
		$str .=	'<option value="'.$key.'" '.$default.'>'.
			$data['visible_name'].
			'</option>';
	}
	
	$str =	'<form action="'.$php_self.'" method="GET">'.
		'<select name="id">'.
		$str.
		'</select>'.
		'<br />'.
		'<input type="submit" value="決定">'.
		'</form>';
	return $str;
}

/**
 * 対人戦用メンバーリストプルダウン
 * 
 * @param	list	[array]		メンバーリスト.
 * @return 	ret	[str]		結果セット(NULLで失敗).
 */
function Show_MemberVsPulldownStr($list, $member_id = 1, $opp_id = 2)
{
	$str = "";
	$str2 = "";
	foreach ($list as $key => $data) {
		if ($key == $member_id) {
			$default1 = "selected";
		} else {
			$default1 = "";
		}
		if ($key == $opp_id) {
			$default2 = "selected";
		} else {
			$default2 = "";
		}
		
		
		$str .=	'<option value="'.$key.'" '.$default1.'>'.
			$data['visible_name'].
			'</option>';
		$str2 .=	'<option value="'.$key.'" '.$default2.'>'.
			$data['visible_name'].
			'</option>';
	}
	
	$str =	'<form action="'.$php_self.'" method="GET">'.
		'<select name="id1">'.
		$str.
		'</select>'.
		'<select name="id2">'.
		$str2.
		'</select>'.
		'<br />'.
		'<input type="submit" value="決定">'.
		'</form>';
	return $str;
}

/**
 * 実績取得sql生成
 * 
 * @param	tcup_id	[int]		開催大会ID.
 * @param	is_id	[int]		ID指定があるか(なければ全員).
 * @return 	ret	[str]		結果セット(NULLで失敗).
 */
function Get_AchievementSQL($tcup_id, $is_id = 1)
{
	$str = 	"SELECT ".
		"	acvc.tcup_member_id ".
		"	,COALESCE(champion_place, 0) AS champion_place ".
		"	,COALESCE(1st_place, 0) AS 1st_place ".
		"	,COALESCE(2nd_place, 0) AS 2nd_place ".
		"	,COALESCE(attend_place, 0) AS attend_place ".
		"	,COALESCE(5th_place, 0) AS 5th_place ".
		"FROM ".
		"	D_TCUP_ATTENDEE acvc ".
		"LEFT JOIN ".
		"	(".
		"		SELECT ".
		"			tcup_member_id".
		"			, SUM( CASE WHEN tcup_type = 2 AND tcup_result_rank =1 THEN 1 ELSE 0 END ) AS champion_place ".
		"			, SUM( CASE WHEN tcup_type = 1 AND tcup_result_rank =1 THEN 1 ELSE 0 END ) AS 1st_place ".
		"			, SUM( CASE WHEN tcup_type = 1 AND tcup_result_rank =2 THEN 1 ELSE 0 END ) AS 2nd_place ".
		"			, SUM( CASE WHEN tcup_type = 1 AND tcup_result_rank IN ( 3, 4 ) THEN 1 ELSE 0 END ) AS attend_place ".
		"			, SUM( CASE WHEN tcup_type = 1 AND tcup_result_rank =5 THEN 1 ELSE 0 END ) AS 5th_place ".
		"		FROM ".
		"			D_TCUP_ATTENDEE acva ".
		"			, M_TCUP acvb ".
		"		WHERE ".
 		"			acvb.tcup_id < {$tcup_id} ".
 		"			AND acva.tcup_id = acvb.tcup_id ".
 		"		GROUP BY ".
 		"			tcup_member_id ".
		"	) acvd ".
 		"	ON ".
 		"		acvc.tcup_member_id = acvd.tcup_member_id ";
	if ($is_id == 1) {
		$str .=	"WHERE ".
			"	acvc.tcup_id = {$tcup_id}";
	}
	return $str;
}

/**
 * 参加回数取得sql生成
 * 
 * @param	tcup_id	[int]		開催大会ID.
 * @param	tcup_type	[int]	開催大会タイプ.
 * @return 	ret	[str]		結果セット(NULLで失敗).
 */
function Get_AttendCountSQL($tcup_id, $tcup_type)
{
	$str =	"SELECT ".
		"	atdA.tcup_member_id ".
		"	,atdA.attend_comment ".
		"	,COALESCE(last_attend_tcup_serial_id, 0) AS last_attend_tcup_serial_id ".
		"	,COALESCE(last_absent_tcup_serial_id, 0) AS last_absent_tcup_serial_id ".
		"	,COALESCE(attend_count, 0) AS attend_count ".
		"	,COALESCE(previous_rank, 0) AS previous_rank ".
		"	,COALESCE(previous_tcup_type, 0) AS previous_tcup_type ".
		"FROM ".
		"	D_TCUP_ATTENDEE atdA ".
		"LEFT JOIN ".
		"	(".
		"		SELECT ".
		"			atda.tcup_member_id ".
		"			, MAX(atdb.tcup_serial_id) AS last_absent_tcup_serial_id ".
		"		FROM ".
		"			M_TCUP_MEMBER atda ".
		"			, M_TCUP atdb ".
		"		WHERE NOT EXISTS (".
 		"			SELECT".
	 	"				*".
	 	"			FROM	".
	 	"				M_TCUP atdc ".
	 	"				, D_TCUP_ATTENDEE atdd ".
 		"			WHERE".
 		"				atdc.tcup_type = {$tcup_type} ".
		"				AND atdc.tcup_id = atdd.tcup_id ".
		"				AND atdc.tcup_id = atdb.tcup_id ".
		"				AND atda.tcup_member_id = atdd.tcup_member_id ".
		"		) ".
		"		AND atdb.tcup_id < {$tcup_id} ".
		"		AND atdb.tcup_type = {$tcup_type} ".
	 	"		GROUP BY ".
	 	"			atda.tcup_member_id ".
		"	) atdB ".
 		"	ON ".
 		"		atdA.tcup_member_id = atdB.tcup_member_id ".
		"LEFT JOIN ".
		"	(".
		"		SELECT ".
		"			atde.tcup_member_id ".
		"			, MAX(atdf.tcup_serial_id) AS last_attend_tcup_serial_id ".
		"			, COUNT(atde.tcup_member_id) AS attend_count ".
		"		FROM ".
		"			D_TCUP_ATTENDEE atde ".
		"			, M_TCUP atdf ".
		"		WHERE".
		"			atde.tcup_id < {$tcup_id} ".
		"			AND atdf.tcup_type = {$tcup_type} ".
		"			AND atde.tcup_id = atdf.tcup_id ".
	 	"		GROUP BY ".
	 	"			atde.tcup_member_id ".
		"	) atdC ".
 		"	ON ".
 		"		atdA.tcup_member_id = atdC.tcup_member_id ".
		"LEFT JOIN ".
		"	(".
		"		SELECT ".
		"			atdg.tcup_member_id ".
		"			, atdg.tcup_result_rank AS previous_rank".
		"			, atdh.tcup_type AS previous_tcup_type".
		"		FROM ".
		"			D_TCUP_ATTENDEE atdg ".
		"			, M_TCUP atdh ".
		"		WHERE".
		"			atdg.tcup_id = ({$tcup_id}-1) ".
		"			AND atdg.tcup_id = atdh.tcup_id ".
		"	) atdD ".
 		"	ON ".
 		"		atdA.tcup_member_id = atdD.tcup_member_id ".
		"WHERE ".
		"	atdA.tcup_id = {$tcup_id} ".
		"GROUP BY	".
		"	tcup_member_id";
	return $str;
}

/**
 * 参加状態文言を返す.
 *   n大会連続m度目.
 *   n大会ぶりm度目.
 * @param	data	[array]		参加状態データ.
 * @return 	ret	[str]		結果セット(NULLで失敗).
 */
function Show_AttendStr($data)
{
	if ($data['attend_count'] == 0) {
		// 初参加.
		$str = "初出場";
	} else if ($data['last_absent_tcup_serial_id'] < $data['last_attend_tcup_serial_id']) {
		// 最終出場の方が近い＝連続出場中.
		$continuous_count = ($data['last_attend_tcup_serial_id'] - $data['last_absent_tcup_serial_id']) + 1;	// 今回でn回連続.
		$str = $continuous_count."大会連続、".($data['attend_count']+1)."度目";
	} else {
		// 最終欠場の方が近い＝久しぶり.
		$continuous_count = ($data['last_absent_tcup_serial_id'] - $data['last_attend_tcup_serial_id']) + 1;	// 今回でn回ぶり.
		$str = $continuous_count."大会ぶり、".($data['attend_count']+1)."度目";
	}
	return $str;
}

/**
 * フルネームを返す.
 * @param	data	[array]		参加状態データ.
 * @return 	ret	[str]		結果セット(NULLで失敗).
 */
function Show_FullnameStr($data)
{
	$str = $data['tcup_member_first_name']." ".$data['tcup_member_last_name'];
	
	return $str;
}

/**
 * 参加一言を返す.
 *   主にNo Comment向け
 * @param	data	[array]		参加状態データ.
 * @return 	ret	[str]		結果セット(NULLで失敗).
 */
function Show_AttendCommentStr($data)
{
	if (!$data['attend_comment']) {
		// 未登録.
		$str = "Under Construction...";
	} else {
		$str = $data['attend_comment'];
	}
	return $str;
}

/**
 * ポイント表示を返す..
 *   主に-ポイント向け
 * @param	point	[float]		数値データ.
 * @param	is_sign	[bool]		符号をつけるか（基本つけない）.
 * @return 	ret	[str]		結果セット(NULLで失敗).
 */
function Show_PointStr($point, $is_sign = false)
{
	if ($point < 0) {
		// マイナス.
		$str = '<font color="#FF0000">'.$point.'</font>';
	} else {
		// プラス.
		if ($is_sign) {
			$str = "+".$point;		// 符号付.
		} else {
			$str = $point;
		}
	}
	return $str;
}

/**
 * 実績文言を返す.
 * @param	data	[array]		実績状態データ.
 * @return 	ret	[str]		結果セット(NULLで失敗).
 */
function Show_AchievementStr($data)
{
	$show_order = array(
				1=>"champion_place",
				2=>"1st_place",
				3=>"2nd_place",
				4=>"attend_place",
				5=>"5th_place",
				);
	$img_name = array(
				1=>"../etc_src/s.ico",
				2=>"../etc_src/1.ico",
				3=>"../etc_src/2.ico",
				4=>"../etc_src/3.ico",
				5=>"../etc_src/5.ico",
				);
	$new_str = '<font color="#FF0000"><blink>New!</blink></font>';
	
	foreach ($show_order as $key => $tmp_name) {
		if (!$data[$tmp_name]) {
			// 0回.何もせず帰る.
			continue;
		}
		for ($i = 0; $i < $data[$tmp_name]; $i++) {
			// 1回以上-表示.
			$str .= '<img src="'.$img_name[$key].'">';
		}
		// 前回受けた実績があればNewマークを付ける.
		$is_new = FALSE;
		switch ($key) {
		case 1:
			// 最強位優勝者.
			if (($data['previous_tcup_type'] == _D_TCUP_TYPE_SPECIAL) && ($data['previous_rank'] == 1)) {
				$is_new = TRUE;
			}
			break;
		case 2:
			// 前回優勝者.
			if (($data['previous_tcup_type'] == _D_TCUP_TYPE_NORMAL) && ($data['previous_rank'] == 1)) {
				$is_new = TRUE;
			}
			break;
		case 3:
			// 前回準優勝.
			if (($data['previous_tcup_type'] == _D_TCUP_TYPE_NORMAL) && ($data['previous_rank'] == 2)) {
				$is_new = TRUE;
			}
			break;
		case 4:
			// 前回決勝進出者.
			if (($data['previous_tcup_type'] == _D_TCUP_TYPE_NORMAL) && (($data['previous_rank'] == 3) || ($data['previous_rank'] == 4))) {
				$is_new = TRUE;
			}
			break;
		case 5:
			// 前回5位.
			if (($data['previous_tcup_type'] == _D_TCUP_TYPE_NORMAL) && (($data['previous_rank'] == 5))) {
				$is_new = TRUE;
			}
			break;
		default:
			break;
		}
		if ($is_new) {
			// 新しければつける.
			$str .= $new_str;
		}
	}
	
	if (!$str) {
		$str = "なし";
	}
	return $str;
}

/**
 * 瞬間風速ポイントランキングリスト取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	ranking_type	[int]		昇順か降順か（1が降順2が昇順）.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupPointRanking($dbo, $ranking_type = 1)
{
	$ranking_array = array(1=>"DESC", 2=>"ASC");
	$rank_str = $ranking_array[$ranking_type];
	
	$SQL =	"SELECT ".
		"	*".
		" FROM ".
		"	D_TCUP_RESULT A".
 		"	,M_TCUP_MEMBER B".
 		"	,M_TCUP C".
		" WHERE ".
		"	A.tcup_member_id = B.tcup_member_id".
		"	AND A.tcup_id = C.tcup_id".
		" ORDER BY ".
		"	result_point {$rank_str}".
		" LIMIT 3";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	$count = 1;
	while ($row = $dbo->fetch_assoc()) {
		$ret[$count] = $row;
		$count++;
	}
	return $ret;
}

/**
 * 予選ポイントランキングリスト取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	ranking_type	[int]		昇順か降順か（1が降順2が昇順）.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupPrePointRanking($dbo, $ranking_type = 1)
{
	$ranking_array = array(1=>"DESC", 2=>"ASC");
	$rank_str = $ranking_array[$ranking_type];
	
	$SQL =	"SELECT ".
		"	*".
		"	,SUM(result_point) AS total_point".
		" FROM ".
		"	D_TCUP_RESULT A".
 		"	,M_TCUP_MEMBER B".
 		"	,M_TCUP C".
		" WHERE ".
		"	A.tcup_member_id = B.tcup_member_id".
		"	AND A.tcup_id = C.tcup_id".
		"	AND C.tcup_type = 1".
		"	AND A.battle_no <= 4".
		" GROUP BY ".
		"	C.tcup_id, B.tcup_member_id".
		" ORDER BY ".
		"	total_point {$rank_str}".
		" LIMIT 3";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	$count = 1;
	while ($row = $dbo->fetch_assoc()) {
		$row['total_point'] = (floor($row['total_point'] * 10) / 10);	// 補正.
		$ret[$count] = $row;
		$count++;
	}
	return $ret;
}

/**
 * 本戦獲得ポイントランキングリスト取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	ranking_type	[int]		昇順か降順か（1が降順2が昇順）.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupFinalPointRanking($dbo, $ranking_type = 1)
{
	$ranking_array = array(1=>"DESC", 2=>"ASC");
	$rank_str = $ranking_array[$ranking_type];
	
	$SQL =	"SELECT ".
		"	*".
		"	,SUM(result_point) AS total_point".
		" FROM ".
		"	D_TCUP_RESULT A".
 		"	,M_TCUP_MEMBER B".
 		"	,M_TCUP C".
		" WHERE ".
		"	A.tcup_member_id = B.tcup_member_id".
		"	AND A.tcup_id = C.tcup_id".
		"	AND C.tcup_type = 1".
		"	AND A.table_no > 1".
		"	AND A.battle_no > 4".
		" GROUP BY ".
		"	C.tcup_id, B.tcup_member_id".
		" ORDER BY ".
		"	total_point {$rank_str}".
		" LIMIT 3";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	$count = 1;
	while ($row = $dbo->fetch_assoc()) {
		$row['total_point'] = (floor($row['total_point'] * 10) / 10);	// 補正.
		$ret[$count] = $row;
		$count++;
	}
	return $ret;
}

/**
 * 決勝卓ポイントランキングリスト取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	ranking_type	[int]		昇順か降順か（1が降順2が昇順）.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupWinnersPointRanking($dbo, $ranking_type = 1)
{
	$ranking_array = array(1=>"DESC", 2=>"ASC");
	$rank_str = $ranking_array[$ranking_type];
	
	$SQL =	"SELECT ".
		"	*".
		"	,SUM(result_point) AS total_point".
		" FROM ".
		"	D_TCUP_RESULT A".
 		"	,M_TCUP_MEMBER B".
 		"	,M_TCUP C".
		" WHERE ".
		"	A.tcup_member_id = B.tcup_member_id".
		"	AND A.tcup_id = C.tcup_id".
		"	AND C.tcup_type = 1".
		"	AND A.table_no = 1".
		"	AND A.battle_no > 4".
		" GROUP BY ".
		"	C.tcup_id, B.tcup_member_id".
		" ORDER BY ".
		"	total_point {$rank_str}".
		" LIMIT 3";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	$count = 1;
	while ($row = $dbo->fetch_assoc()) {
		$row['total_point'] = (floor($row['total_point'] * 10) / 10);	// 補正.
		$ret[$count] = $row;
		$count++;
	}
	return $ret;
}

/**
 * 対個人戦績データ取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	member_id	[int]		メンバーID.
 * @param	opp_id		[int]		対戦者ID.
 * @param	tcup_type	[int]		大会タイプ.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupVsResult($dbo, $member_id, $opp_id, $tcup_type = 1)
{
	$SQL =	"SELECT ".
		"	C.*".
		"	,M.*".
		" FROM ".
		"	D_TCUP_RESULT A".
 		"	,D_TCUP_RESULT B".
 		"	,D_TCUP_RESULT C".
 		"	,M_TCUP M".
		" WHERE ".
		"	A.tcup_member_id = {$member_id} ".
		"	AND B.tcup_member_id = {$opp_id} ".
		"	AND B.tcup_id = A.tcup_id".
		"	AND B.battle_no = A.battle_no".
		"	AND B.table_no = A.table_no".
		"	AND C.tcup_id = B.tcup_id".
		"	AND C.battle_no = B.battle_no".
		"	AND C.table_no = B.table_no".
		"	AND M.tcup_type = {$tcup_type}".
		"	AND A.tcup_id = M.tcup_id".
		" ORDER BY ".
		"	C.tcup_id ASC, C.battle_no ASC, C.result_rank ASC";	// 対戦していれば同卓なのでバトル順だけ見ればOK
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		// 今回は戦績なしが十分ありうるので空を返す.
		return array();
	}
	while ($row = $dbo->fetch_assoc()) {
		// 大会／対戦／テーブル／順位(同着があるので添え字入れない).
		$ret[$row['tcup_id']][$row['battle_no']][$row['table_no']][] = $row;
	}
	return $ret;
}

/**
 * 大会戦績データ取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	member_id	[int]		メンバーID.
 * @param	tcup_type	[int]		大会タイプ.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupResult($dbo, $member_id, $tcup_type = 1)
{
	$SQL =	"SELECT ".
		"	C.*".
		"	,M.*".
		" FROM ".
		"	D_TCUP_RESULT A".
 		"	,D_TCUP_RESULT C".
 		"	,M_TCUP M".
		" WHERE ".
		"	A.tcup_member_id = {$member_id} ".
		"	AND C.tcup_id = A.tcup_id".
		"	AND C.battle_no = A.battle_no".
		"	AND C.table_no = A.table_no".
		"	AND M.tcup_type = {$tcup_type}".
		"	AND A.tcup_id = M.tcup_id".
		" ORDER BY ".
		"	C.tcup_id ASC, C.battle_no ASC, C.result_rank ASC";	// 対戦していれば同卓なのでバトル順だけ見ればOK
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		// 今回は戦績なしが十分ありうるので空を返す.
		return array();
	}
	while ($row = $dbo->fetch_assoc()) {
		// 大会／対戦／テーブル／順位(同着があるので添え字入れない).
		$ret[$row['tcup_id']][$row['battle_no']][$row['table_no']][] = $row;
	}
	return $ret;
}

/**
 * 大会参加/実績データを全員分取得
 * ※最強位以外.
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	tcup_type	[int]		最強位か（1が通常2が最強位）.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupAttendeeData2($dbo, $tcup_type = 1)
{
	$SQL =	"SELECT ".
		"	MAX(tcup_id) AS tcup_id".
		" FROM ".
		"	M_TCUP";
		" WHERE ".
		"	tcup_type = {$tcup_type}";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	$max_row = $dbo->fetch_assoc();
	$tcup_id = ($max_row['tcup_id'] + 1);
	
	$SQL =	"SELECT ".
		"	*".
		" FROM ".
		"	(".Get_AchievementSQL($tcup_id, 0).") achievement ".
		"	INNER JOIN M_TCUP_MEMBER A ON achievement.tcup_member_id = A.tcup_member_id".
		"	INNER JOIN ".
		"	(".
		"		SELECT".
		"			tcup_member_id".
		"			, COUNT(tcup_id) AS attend_count".
		"		FROM ".
		"			D_TCUP_ATTENDEE ".
		"		WHERE ".
		"			tcup_result_rank > 0 ".
		"			AND tcup_id IN ( ".
		"				SELECT ".
		"					tcup_id ".
		"				FROM ".
		"					M_TCUP ".
		"				WHERE ".
		"					tcup_type = {$tcup_type} ".
		"				)".
		"		GROUP BY	".
		"			tcup_member_id	".
		"	) B ON A.tcup_member_id = B.tcup_member_id".
		" GROUP BY ".
		"	A.tcup_member_id".
		" ORDER BY ".
		"	attend_count DESC, A.tcup_member_id DESC";			// 回数降順、ID降順.
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		echo "No data...";
		exit();
	}
	while ($row = $dbo->fetch_assoc()) {
		// 回数／メンバー.
		$ret[$row['attend_count']][$row['tcup_member_id']] = $row;
	}
	return $ret;
}

/**
 * 大会データ取得
 * 大会詳細と参加人数を受け取る
 * 
 * @param	dbo		[Object]	DBObject.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupList($dbo)
{
	$SQL =	"SELECT ".
		"	A.*".
		"	,COUNT(B.tcup_member_id) AS member_count".
		" FROM ".
		"	M_TCUP A".
 		"	,D_TCUP_ATTENDEE B".
		" WHERE ".
		"	A.tcup_id = B.tcup_id ".
		" GROUP BY ".
		"	B.tcup_id";
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		// データなしはエラー.
		echo "No data...";
		exit();
	}
	while ($row = $dbo->fetch_assoc()) {
		// 大会ID昇順.
		$ret[$row['tcup_id']] = $row;
	}
	return $ret;
}

/**
 * 大会入賞者一覧取得
 * 入賞者と詳細を受け取る
 * 
 * @param	dbo		[Object]	DBObject.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupPrizewinner($dbo)
{
	$SQL =	"SELECT ".
		"	A.*".
		"	,B.*".
		" FROM ".
		"	M_TCUP_MEMBER A".
 		"	,D_TCUP_ATTENDEE B".
		" WHERE ".
		"	A.tcup_member_id = B.tcup_member_id ".
		"	AND B.tcup_result_rank IN (1,2,3,4,5) ".	// 5位まで入賞.
		"ORDER BY ".
		"	tcup_id ASC, tcup_result_rank ASC";			// 大会ID昇順、順位昇順..
	if (!Execute_Query($dbo, $SQL)) {
		echo "SQL Error.";
		exit();
	}
	if ($dbo->num_rows() < 1) {
		// データなしはエラー.
		echo "No data...";
		exit();
	}
	while ($row = $dbo->fetch_assoc()) {
		// 大会ID昇順.順位昇順.
		$ret[$row['tcup_id']][$row['tcup_result_rank']] = $row;
	}
	return $ret;
}

/**
 * 回戦数から状態を示す情報を返す
 * ※4回戦まで予選、5回戦から本線.
 * ※5回戦目の1番テーブルは決勝卓.
 * 
 * @param	battle_no	[int]	回線数
 * @param	table_no	[int]	テーブル番号.
 * @return 	str		[string]	結果文字列(予選|本戦|決勝卓)N回戦.
 */
function Get_TcupBattleNumText($battle_no, $table_no)
{
	if ($battle_no < 5) {
		// 予選.
		$str = "予選 {$battle_no}回戦 {$table_no}番卓";
	} else {
		// 本戦
		$show_cnt = $battle_no - 4;			// 本戦は1回戦からカウント.
		if ($table_no == 1) {
			// 決勝卓.
			$str = "決勝卓 {$show_cnt}回戦";
		} else {
			// 本戦.
			$str = "本戦 {$show_cnt}回戦 {$table_no}番卓";
		}
	}
	return $str;
}


?>
