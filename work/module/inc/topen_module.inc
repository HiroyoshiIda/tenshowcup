<?php
// topen_module.
// 天翔杯オープン戦utility.

	$_G_Topen_prefix =	array(
							0 => array(0 => "nono_", 1 => "noyes_"),			// 赤ナシヤキトリ
							1 => array(0 => "yesno_", 1 => "yesyes_"),			// 赤アリヤキトリ
						);

	$_G_Existence_text = array(
		0 => "なし",							// ありなしテキスト,
		1 => "あり",							// ありなしテキスト,
	);

/**
 * 個人成績取得
 * 
 * @param	dbo	[Object]	DBObject.
 * @param	member_id	[int]	tcup_member_id.
 * @param	is_rtd	[int]	RTD模擬か.
 * @return 	row	[array]		結果セット(NULLで失敗).
 */
function Get_PersonnelResult($dbo, $member_id, $is_rtd = 0)
{
	$tables_sql = Make_PersonnelResultSQL($member_id, $is_rtd);					// 結合したテーブルをもらう.
	
	$SQL =	
		"SELECT ".
		"	* ".
		" FROM ".
		"	{$tables_sql} ".
		" WHERE ".
		"	D.tcup_member_id = {$member_id} ";									// 全データだけDテーブルとしている.
		
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
 * 個人成績取得用SQL取得
 * 
 * @param	member_id	[int]	tcup_member_id.
 * @param	is_rtd		[int]	RTD模擬か.
 * @return 	row	[array]		結果セット(NULLで失敗).
 */
function Make_PersonnelResultSQL($member_id, $is_rtd = 0)
{
	global $_G_Topen_prefix;
	
	// フルSQL.
	$sql = 	"( ".
					"SELECT ".
					"	tcup_member_id ".
					"	,COUNT(tcup_member_id) AS play_count ".
					"	,COUNT(DISTINCT(D_TOPEN_RESULT.topen_id)) AS attend_count ".
					"	,SUM(CASE WHEN result_rank = 1 THEN 1 ELSE 0 END) AS 1st_count ".
					"	,SUM(CASE WHEN result_rank = 2 THEN 1 ELSE 0 END) AS 2nd_count ".
					"	,SUM(CASE WHEN result_rank = 3 THEN 1 ELSE 0 END) AS 3rd_count ".
					"	,SUM(CASE WHEN result_rank = 4 THEN 1 ELSE 0 END) AS 4th_count ".
					"	,SUM(result_point) AS total_point ".
					"	,AVG(result_point) AS average_point ".
					"	,AVG(result_rank) AS average_rank ".
					"	,MAX(result_point) AS max_point ".
					"	,MIN(result_point) AS min_point ".
					"FROM ".
					"	D_TOPEN_RESULT ".
					"	, M_TOPEN ".
					"WHERE ".	
					"	tcup_member_id = {$member_id} ".
					"	AND M_TOPEN.topen_id = D_TOPEN_RESULT.topen_id ".
					"	AND M_TOPEN.is_rtd = {$is_rtd} ".
				") D ";

	// 赤とヤキトリでカラムとテーブルを生成.
	for ($red = 0; $red < 2; $red++) {
		for ($yakitori = 0; $yakitori < 2; $yakitori++) {
			$sql .= 	" LEFT JOIN (".						// そのルールで打ってない＝NULLがありうるので基本データにつなげる.
									"SELECT ".
									"	tcup_member_id ".
									"	,SUM(CASE WHEN result_rank = 1 THEN 1 ELSE 0 END) AS {$_G_Topen_prefix[$red][$yakitori]}1st_count ".
									"	,SUM(CASE WHEN result_rank = 2 THEN 1 ELSE 0 END) AS {$_G_Topen_prefix[$red][$yakitori]}2nd_count ".
									"	,SUM(CASE WHEN result_rank = 3 THEN 1 ELSE 0 END) AS {$_G_Topen_prefix[$red][$yakitori]}3rd_count ".
									"	,SUM(CASE WHEN result_rank = 4 THEN 1 ELSE 0 END) AS {$_G_Topen_prefix[$red][$yakitori]}4th_count ".
									"	,SUM(result_point) AS {$_G_Topen_prefix[$red][$yakitori]}total_point ".
									"	,AVG(result_point) AS {$_G_Topen_prefix[$red][$yakitori]}average_point ".
									"	,AVG(result_rank) AS {$_G_Topen_prefix[$red][$yakitori]}average_rank ".
									"	,MAX(result_point) AS {$_G_Topen_prefix[$red][$yakitori]}max_point ".
									"	,MIN(result_point) AS {$_G_Topen_prefix[$red][$yakitori]}min_point ".
									"FROM ".
									"	D_TOPEN_RESULT {$_G_Topen_prefix[$red][$yakitori]}d ".
									"	, M_TOPEN {$_G_Topen_prefix[$red][$yakitori]}m ".
									"WHERE ".	
									"	{$_G_Topen_prefix[$red][$yakitori]}m.topen_id = {$_G_Topen_prefix[$red][$yakitori]}d.topen_id ".
									"	AND {$_G_Topen_prefix[$red][$yakitori]}d.tcup_member_id = {$member_id} ".
									"	AND {$_G_Topen_prefix[$red][$yakitori]}m.is_red = {$red} ".
									"	AND {$_G_Topen_prefix[$red][$yakitori]}m.is_yakitori = {$yakitori} ".
									"	AND {$_G_Topen_prefix[$red][$yakitori]}m.is_rtd = {$is_rtd} ".
						") {$_G_Topen_prefix[$red][$yakitori]}all ON ".
							" {$_G_Topen_prefix[$red][$yakitori]}all.tcup_member_id = D.tcup_member_id ";

		}
	}
	return $sql;
}

/**
 * メンバーリスト取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	is_rtd	[int]		RTD模擬か.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupMemberList($dbo, $is_rtd = 0)
{
	$SQL =	"SELECT ".
		"	A.*".
		"	,(CASE WHEN MAX(C.topen_id) = MIN(C.topen_id) THEN 1 ELSE 0 END) AS is_guest ".	// ゲストチェック.
		" FROM ".
		"	M_TCUP_MEMBER A".
		"	,M_TOPEN B".
		"	,D_TOPEN_ATTENDEE C".
		" WHERE ".
		"	B.topen_id = C.topen_id".
		"	AND B.is_rtd = {$is_rtd}".
		"	AND C.tcup_member_id = A.tcup_member_id".
		"	AND C.topen_result_rank IS NOT NULL ".
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
 * 対個人戦績データ取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	member_id	[int]		メンバーID.
 * @param	opp_id		[int]		対戦者ID.
 * @param	is_rtd	[int]		RTD模擬か.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TopenVsResult($dbo, $member_id, $opp_id, $is_rtd = 0)
{
	$SQL =	"SELECT ".
		"	C.*".
		"	,M.*".
		" FROM ".
		"	D_TOPEN_RESULT A".
 		"	,D_TOPEN_RESULT B".
 		"	,D_TOPEN_RESULT C".
 		"	,M_TOPEN M".
		" WHERE ".
		"	A.tcup_member_id = {$member_id} ".
		"	AND B.tcup_member_id = {$opp_id} ".
		"	AND B.topen_id = A.topen_id".
		"	AND B.battle_no = A.battle_no".
		"	AND B.table_no = A.table_no".
		"	AND C.topen_id = B.topen_id".
		"	AND C.battle_no = B.battle_no".
		"	AND C.table_no = B.table_no".
		"	AND A.topen_id = M.topen_id".
		"	AND M.is_rtd = {$is_rtd}".
		" ORDER BY ".
		"	C.topen_id ASC, C.battle_no ASC, C.result_rank ASC";	// 対戦していれば同卓なのでバトル順だけ見ればOK
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
		$ret[$row['topen_id']][$row['battle_no']][$row['table_no']][] = $row;
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
 * ポイント表示を返す..
 *   主に-ポイント向け
 * @param	point	[float]		数値データ.
 * @param	is_sign	[bool]		符号をつけるか（基本つけない）.
 * @return 	ret	[str]		結果セット(NULLで失敗).
 */
function Show_PointStr($point, $is_sign = false)
{
	if (is_numeric($point)) {
		// 数字だったら表示.
		$point = round($point, 2);								// やりたくないけど2桁目で丸め.
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
	} else {
		// 数字じゃなければ棒線.
		$str = "－";
	}
	return $str;
}

/**
 * 回戦数から状態を示す情報を返す
 * 
 * @param	battle_no	[int]	回線数
 * @param	table_no	[int]	テーブル番号.
 * @return 	str		[string]	結果文字列(予選|本戦|決勝卓)N回戦.
 */
function Get_TopenBattleNumText($battle_no, $table_no)
{
	$str = "{$battle_no}回戦 {$table_no}番卓";
	return $str;
}

/**
 * ヤキトリとチョンボ情報についてアイコンを付けて返す
 * 
 * @param	result		[array]	D_TOPEN_RESULT
 * @return 	str		[string]	結果文字列(予選|本戦|決勝卓)N回戦.
 */
function Get_YakitoriFaultIcon($result)
{
	$str = "";
	$yakitori_img = "../etc_src/chicken.ico";
	
	if ($result['is_yakitori_get'] == 1) {
		$str = '<img src="'.$yakitori_img.'">';
	}
	// ToDo-チョンボはまた後日.
	
	return $str;
}

// =========== ここまで移植 ===========================================================================

/**
 * 対人戦績
 * 
 * @param	dbo	[Object]	DBObject.
 * @param	member_id	[int]	tcup_member_id.
 * @param	is_rtd	[int]	RTD模擬か（0:通常、1:RTD模擬）.
 * @return 	row	[array]		結果セット(NULLで失敗).
 */
function Get_PersonnelOPResult($dbo, $member_id, $is_rtd = 0)
{
	$SQL =	"SELECT ".
		"	A.tcup_member_id ".
		"	,COUNT(A.tcup_member_id) AS battle_count".
		"	,SUM(CASE WHEN A.result_point < 0 AND B.result_point > 0 THEN 1 ELSE 0 END) AS win_count".
		"	,SUM(CASE WHEN A.result_point > 0 AND B.result_point < 0 THEN 1 ELSE 0 END) AS lose_count".
		"	,SUM(CASE WHEN A.result_point < B.result_point THEN 1 ELSE -1 END) AS compatible_point".
		" FROM ".
		"	D_TOPEN_RESULT A".
		"	,D_TOPEN_RESULT B".
		"	,M_TOPEN C".
		" WHERE ".
		"	C.topen_id = A.topen_id ".
		"	AND C.topen_id = B.topen_id ".
		"	AND C.is_rtd = {$is_rtd} ".
		"	AND A.topen_id = B.topen_id ".
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
 * 大会参加者リスト取得
 * 
 * @param	dbo		[Object]	DBObject.
 * @param	topen_id		[int]		開催大会ID.
 * @param	tcup_type	[int]		最強位か（1が通常2が最強位）.
 * @return 	ret		[array]		結果セット(NULLで失敗).
 */
function Get_TcupAttendeeList($dbo, $topen_id, $tcup_type = 1)
{
	$SQL =	"SELECT ".
		"	*".
		" FROM ".
		"	M_TCUP_MEMBER A".
 		"	,(".Get_AttendCountSQL($topen_id, $tcup_type).") attend ".
 		"	,(".Get_AchievementSQL($topen_id).") achievement ".
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
//function Get_TcupAttendeeData($dbo, $tcup_member_id, $tcup_type = 1)
//{
//	$SQL =	"SELECT ".
//		"	MAX(topen_id) AS topen_id".
//		" FROM ".
//		"	M_TOPEN";
//	if (!Execute_Query($dbo, $SQL)) {
//		echo "SQL Error.";
//		exit();
//	}
//	if ($dbo->num_rows() < 1) {
//		echo "No data...";
//		exit();
//	}
//	$max_row = $dbo->fetch_assoc();
//	$topen_id = ($max_row['topen_id'] + 1);
//	
//	$SQL =	"SELECT ".
//		"	*".
//		" FROM ".
//		"	(".Get_AchievementSQL($topen_id, 0).") achievement ".
//		"	INNER JOIN M_TCUP_MEMBER A ON achievement.tcup_member_id = A.tcup_member_id".
//		"	INNER JOIN ".
//		"	(".
//		"		SELECT".
//		"			tcup_member_id".
//		"			, COUNT(topen_id) AS attend_count".
//		"		FROM ".
//		"			D_TOPEN_ATTENDEE ".
//		"		WHERE ".
//		"			tcup_member_id = {$tcup_member_id} ".
//		"			AND tcup_result_rank > 0 ".
//		"			AND topen_id IN ( ".
//		"				SELECT ".
//		"					topen_id ".
//		"				FROM ".
//		"					M_TOPEN ".
//		"				)".
//		"	) B ON A.tcup_member_id = B.tcup_member_id".
//		" WHERE ".
//		"	A.tcup_member_id = {$tcup_member_id}".
//		" GROUP BY ".
//		"	A.tcup_member_id";
//	if (!Execute_Query($dbo, $SQL)) {
//		echo "SQL Error.";
//		exit();
//	}
//	if ($dbo->num_rows() < 1) {
//		echo "No data...";
//		exit();
//	}
//	$ret = $dbo->fetch_assoc();
//	return $ret;
//}

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
		"	D_TOPEN_YAKUMAN_GETTER A".
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
		$ret[$row['topen_id']][] = $row;
	}
	return $ret;
}

/**
 * 実績取得sql生成
 * 
 * @param	topen_id	[int]		開催大会ID.
 * @param	is_id	[int]		ID指定があるか(なければ全員).
 * @return 	ret	[str]		結果セット(NULLで失敗).
 */
//function Get_AchievementSQL($topen_id, $is_id = 1)
//{
//	$str = 	"SELECT ".
//		"	acvc.tcup_member_id ".
//		"	,COALESCE(champion_place, 0) AS champion_place ".
//		"	,COALESCE(1st_place, 0) AS 1st_place ".
//		"	,COALESCE(2nd_place, 0) AS 2nd_place ".
//		"	,COALESCE(attend_place, 0) AS attend_place ".
//		"	,COALESCE(5th_place, 0) AS 5th_place ".
//		"FROM ".
//		"	D_TOPEN_ATTENDEE acvc ".
//		"LEFT JOIN ".
//		"	(".
//		"		SELECT ".
//		"			tcup_member_id".
//		"			, SUM( CASE WHEN tcup_type = 2 AND tcup_result_rank =1 THEN 1 ELSE 0 END ) AS champion_place ".
//		"			, SUM( CASE WHEN tcup_type = 1 AND tcup_result_rank =1 THEN 1 ELSE 0 END ) AS 1st_place ".
//		"			, SUM( CASE WHEN tcup_type = 1 AND tcup_result_rank =2 THEN 1 ELSE 0 END ) AS 2nd_place ".
//		"			, SUM( CASE WHEN tcup_type = 1 AND tcup_result_rank IN ( 3, 4 ) THEN 1 ELSE 0 END ) AS attend_place ".
//		"			, SUM( CASE WHEN tcup_type = 1 AND tcup_result_rank =5 THEN 1 ELSE 0 END ) AS 5th_place ".
//		"		FROM ".
//		"			D_TOPEN_ATTENDEE acva ".
//		"			, M_TOPEN acvb ".
//		"		WHERE ".
//		"			acvb.topen_id < {$topen_id} ".
//		"			AND acva.topen_id = acvb.topen_id ".
//		"		GROUP BY ".
//		"			tcup_member_id ".
//		"	) acvd ".
//		"	ON ".
//		"		acvc.tcup_member_id = acvd.tcup_member_id ";
//	if ($is_id == 1) {
//		$str .=	"WHERE ".
//			"	acvc.topen_id = {$topen_id}";
//	}
//	return $str;
//}

/**
 * 参加回数取得sql生成
 * 
 * @param	topen_id	[int]		開催大会ID.
 * @param	tcup_type	[int]	開催大会タイプ.
 * @return 	ret	[str]		結果セット(NULLで失敗).
 */
function Get_AttendCountSQL($topen_id, $tcup_type)
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
		"	D_TOPEN_ATTENDEE atdA ".
		"LEFT JOIN ".
		"	(".
		"		SELECT ".
		"			atda.tcup_member_id ".
		"			, MAX(atdb.tcup_serial_id) AS last_absent_tcup_serial_id ".
		"		FROM ".
		"			M_TCUP_MEMBER atda ".
		"			, M_TOPEN atdb ".
		"		WHERE NOT EXISTS (".
 		"			SELECT".
	 	"				*".
	 	"			FROM	".
	 	"				M_TOPEN atdc ".
	 	"				, D_TOPEN_ATTENDEE atdd ".
 		"			WHERE".
 		"				atdc.tcup_type = {$tcup_type} ".
		"				AND atdc.topen_id = atdd.topen_id ".
		"				AND atdc.topen_id = atdb.topen_id ".
		"				AND atda.tcup_member_id = atdd.tcup_member_id ".
		"		) ".
		"		AND atdb.topen_id < {$topen_id} ".
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
		"			D_TOPEN_ATTENDEE atde ".
		"			, M_TOPEN atdf ".
		"		WHERE".
		"			atde.topen_id < {$topen_id} ".
		"			AND atdf.tcup_type = {$tcup_type} ".
		"			AND atde.topen_id = atdf.topen_id ".
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
		"			D_TOPEN_ATTENDEE atdg ".
		"			, M_TOPEN atdh ".
		"		WHERE".
		"			atdg.topen_id = ({$topen_id}-1) ".
		"			AND atdg.topen_id = atdh.topen_id ".
		"	) atdD ".
 		"	ON ".
 		"		atdA.tcup_member_id = atdD.tcup_member_id ".
		"WHERE ".
		"	atdA.topen_id = {$topen_id} ".
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
			if (($data['previous_tcup_type'] == _D_TOPEN_TYPE_SPECIAL) && ($data['previous_rank'] == 1)) {
				$is_new = TRUE;
			}
			break;
		case 2:
			// 前回優勝者.
			if (($data['previous_tcup_type'] == _D_TOPEN_TYPE_NORMAL) && ($data['previous_rank'] == 1)) {
				$is_new = TRUE;
			}
			break;
		case 3:
			// 前回準優勝.
			if (($data['previous_tcup_type'] == _D_TOPEN_TYPE_NORMAL) && ($data['previous_rank'] == 2)) {
				$is_new = TRUE;
			}
			break;
		case 4:
			// 前回決勝進出者.
			if (($data['previous_tcup_type'] == _D_TOPEN_TYPE_NORMAL) && (($data['previous_rank'] == 3) || ($data['previous_rank'] == 4))) {
				$is_new = TRUE;
			}
		case 5:
			// 前回5位.
			if (($data['previous_tcup_type'] == _D_TOPEN_TYPE_NORMAL) && (($data['previous_rank'] == 5))) {
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
		"	D_TOPEN_RESULT A".
 		"	,M_TCUP_MEMBER B".
 		"	,M_TOPEN C".
		" WHERE ".
		"	A.tcup_member_id = B.tcup_member_id".
		"	AND A.topen_id = C.topen_id".
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
		"	D_TOPEN_RESULT A".
 		"	,M_TCUP_MEMBER B".
 		"	,M_TOPEN C".
		" WHERE ".
		"	A.tcup_member_id = B.tcup_member_id".
		"	AND A.topen_id = C.topen_id".
		"	AND C.tcup_type = 1".
		"	AND A.battle_no <= 4".
		" GROUP BY ".
		"	C.topen_id, B.tcup_member_id".
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
		"	D_TOPEN_RESULT A".
 		"	,M_TCUP_MEMBER B".
 		"	,M_TOPEN C".
		" WHERE ".
		"	A.tcup_member_id = B.tcup_member_id".
		"	AND A.topen_id = C.topen_id".
		"	AND C.tcup_type = 1".
		"	AND A.table_no > 1".
		"	AND A.battle_no > 4".
		" GROUP BY ".
		"	C.topen_id, B.tcup_member_id".
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
		"	D_TOPEN_RESULT A".
 		"	,M_TCUP_MEMBER B".
 		"	,M_TOPEN C".
		" WHERE ".
		"	A.tcup_member_id = B.tcup_member_id".
		"	AND A.topen_id = C.topen_id".
		"	AND C.tcup_type = 1".
		"	AND A.table_no = 1".
		"	AND A.battle_no > 4".
		" GROUP BY ".
		"	C.topen_id, B.tcup_member_id".
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
		"	M_TOPEN A".
 		"	,D_TOPEN_ATTENDEE B".
		" WHERE ".
		"	A.topen_id = B.topen_id ".
		" GROUP BY ".
		"	B.topen_id";
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
		$ret[$row['topen_id']] = $row;
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
 		"	,D_TOPEN_ATTENDEE B".
		" WHERE ".
		"	A.tcup_member_id = B.tcup_member_id ".
		"	AND B.tcup_result_rank IN (1,2,3,4,5) ".	// 5位まで入賞.
		"ORDER BY ".
		"	topen_id ASC, tcup_result_rank ASC";			// 大会ID昇順、順位昇順..
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
		$ret[$row['topen_id']][$row['tcup_result_rank']] = $row;
	}
	return $ret;
}

?>
