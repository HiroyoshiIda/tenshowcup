<?php
// ------------------------------.
// 天翔杯 - Total result.
// ------------------------------.
// D_TCUP_RESULTを総計して、総合、予選、本戦の成績を分析する.

ini_set('display_errors', 1);
	
// -------------
// Include.
// -------------
	$cur_dir = getcwd();						// カレントのディレクトリを取得.
	$dir = dirname(__FILE__);					// ディレクトリ位置取得.
	
	chdir( $dir );							// ディレクトリ移動.
	require_once '../../../work/module/inc/define.inc';		// util読み込み.
	chdir( $cur_dir );						// 元ディレクトリに移動.
	
	require_once _D_INCLUDE_PATH.'/base_module.inc';
	require_once _D_INCLUDE_PATH.'/tcup_module.inc';
	
// -------------
// 変数宣言.
// -------------
	
	// 外部入力の受取.
	if (isset($_REQUEST['id'])) {					// IDの入力がある.
		$member_id = $_REQUEST['id'];
	} else {
		$member_id = 0;						// ないなら初期値.
	}
	
	if (!is_numeric($member_id)) {
		exit("入力が不正です");
	}
	
// -------------
// DB接続.
// -------------

	$dbo = Connect_DB();
	if ($dbo->link == NULL) {
		echo "Not Connect.";
		exit();
	}

// -------------
// データ取得.
// -------------
	
	$member_list = Get_TcupMemberList($dbo);
	if (!$member_list) {
		echo "No Member List...";
		exit();
	}
	
	if ($member_id != 0) {
		// 実績取得.
		$achieve = Get_TcupAttendeeData($dbo, $member_id);
		if (!$achieve) {
			echo "Illegal Achieve Data";
			exit();
		}
		// 個人戦績取得.
		$result = Get_PersonnelResult($dbo, $member_id);
		if (!$result) {
			echo "Illegal Personnel Data";
			exit();
		}
		// 対人戦績.
		$opp = Get_PersonnelOPResult($dbo, $member_id);
		if (!$opp) {
			echo "Illegal Personnel Data";
			exit();
		}
	}
	
// -------------
// 文言整形.
// -------------
	
	$total_point = (floor($result['total_point'] * 10) / 10);	// 補正.
	$max_point = (floor($result['max_point'] * 10) / 10);		// 補正.
	$min_point = (floor($result['min_point'] * 10) / 10);		// 補正.
	$average_point = (floor($result['average_point'] * 10) / 10);	// 補正.
	$member_name = $member_list[$member_id]['visible_name'];
	
	if ($member_id != 0) {
		$guest_cnt = 0;
		$member_cnt = 0;
		$guest_str = "";
		$member_str = "";
		$show_color = array(0=>"#FAFFFF", 1=>"#FFFACD");
		foreach ($opp as $key => $data) {
			if ($member_list[$data['tcup_member_id']]['is_guest']) {
				// ゲスト.
				$show_cnt = $guest_cnt++;
			} else {
				// メンバー
				$show_cnt = $member_cnt++;
			}
			$color_no = $show_cnt % 2;				// 表示用.
			$str = 		
				'<tr>'.
					'<td align="center" bgcolor="'.$show_color[$color_no].'">'.
						'<a href="./total_result.php?id='.$data['tcup_member_id'].'">'.$member_list[$data['tcup_member_id']]['visible_name'].'</a>'.
					'</td>'.
					'<td align="center" bgcolor="'.$show_color[$color_no].'">'.
						$data['battle_count'].
					'</td>'.
					'<td align="center" bgcolor="'.$show_color[$color_no].'">'.
						$data['win_count'].
					'</td>'.
					'<td align="center" bgcolor="'.$show_color[$color_no].'">'.
						$data['lose_count'].
					'</td>'.
					'<td align="center" bgcolor="'.$show_color[$color_no].'">'.
						'<a href="./vs_result.php?id1='.$member_id.'&id2='.$data['tcup_member_id'].'">'.Show_PointStr($data['compatible_point'],true).'</a>'.
					'</td>'.
				'</tr>';
			if ($member_list[$data['tcup_member_id']]['is_guest']) {
				// ゲスト.
				$guest_str .= $str;
			} else {
				// メンバー
				$member_str .= $str;
			}
		}
	}
	
// -------------
// 表示.
// -------------
	
echo
	'<html>',
	'<head>',
	  '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">',
	  '<title>天翔杯</title>',
	'</head>',
	'<body bgcolor="#FAFFFF">',
	'<div style="margin-left: 60px; margin-right: 60px">',
		'<br>',
		'<center><FONT size=+3><b>個人戦績-天翔杯総合</b></FONT><br></center>',
		'<hr width="100%">',
		'<FONT size=+1>',
		'<center>',
			'天翔杯',
			'&nbsp; &nbsp; &nbsp; &nbsp; ',
			'<a href="./total_sp_result.php">最強位</a>',
			'&nbsp; &nbsp; &nbsp; &nbsp; ',
			'<a href="./ranking.php">ランキング</a>',
		'</center>',
		'<hr width="100%">',
		'<center>',
		'参加者を選んでください。<br />',
		Show_MemberPulldownStr($member_list, $member_id),
		'</center>',
		'<hr width="100%">';
	if ($member_id != 0) {
	echo
		$member_name,'さんの成績','<br />',
		'<br />',
		'参加情報',
		'<table border=1>',
			'<tbody>',
				'<tr>',
					'<th bgcolor="#00ff7f">',
						'参加回数',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'実績',
					'</th>',
				'</tr>',
				'<tr>',
					'<td align="center">',
						'<a href="./tcup_result.php?id=',$member_id,'">',$achieve['attend_count'],'回','</a><br>',
					'</td>',
					'<td align="center">',
						Show_AchievementStr($achieve),
					'</td>',
				'</tr>',
			'</tbody>',
		'</table>',
		'<br />',
		'着順情報',
		'<table border=1>',
			'<tbody>',
				'<tr>',
					'<th bgcolor="#00ff7f">',
						'　種別　',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　1位　',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　2位　',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　3位　',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　4位　',
					'</th>',
				'</tr>',
				'<tr>',
					'<td align="center">',
						'予選',
					'</td>',
					'<td align="center">',
						$result['pre_1st_count'],
					'</td>',
					'<td align="center">',
						$result['pre_2nd_count'],
					'</td>',
					'<td align="center">',
						$result['pre_3rd_count'],
					'</td>',
					'<td align="center">',
						$result['pre_4th_count'],
					'</td>',
				'</tr>',
				'<tr>',
					'<td align="center">',
						'本戦',
					'</td>',
					'<td align="center">',
						$result['losers_1st_count'],
					'</td>',
					'<td align="center">',
						$result['losers_2nd_count'],
					'</td>',
					'<td align="center">',
						$result['losers_3rd_count'],
					'</td>',
					'<td align="center">',
						$result['losers_4th_count'],
					'</td>',
				'</tr>',
				'<tr>',
					'<td align="center">',
						'決勝卓',
					'</td>',
					'<td align="center">',
						$result['winners_1st_count'],
					'</td>',
					'<td align="center">',
						$result['winners_2nd_count'],
					'</td>',
					'<td align="center">',
						$result['winners_3rd_count'],
					'</td>',
					'<td align="center">',
						$result['winners_4th_count'],
					'</td>',
				'</tr>',
				'<tr>',
					'<td align="center" bgcolor="#ffc0cb">',
						'合計',
					'</td>',
					'<td align="center" bgcolor="#ffc0cb">',
						$result['1st_count'],
					'</td>',
					'<td align="center" bgcolor="#ffc0cb">',
						$result['2nd_count'],
					'</td>',
					'<td align="center" bgcolor="#ffc0cb">',
						$result['3rd_count'],
					'</td>',
					'<td align="center" bgcolor="#ffc0cb">',
						$result['4th_count'],
					'</td>',
				'</tr>',
			'</tbody>',
		'</table>',
		'※予選は4回戦まで、本戦は決勝卓以外の5回戦以降を指します。<br />',
		'<br />',
		'獲得ポイント情報',
		'<table border=1>',
			'<tbody>',
				'<tr>',
					'<th bgcolor="#00ff7f">',
						'最大',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'最小',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'平均',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'合計',
					'</th>',
				'</tr>',
				'<tr>',
					'<td align="center">',
						Show_PointStr($max_point),'pts.',
					'</td>',
					'<td align="center">',
						Show_PointStr($min_point),'pts.',
					'</td>',
					'<td align="center">',
						Show_PointStr($average_point),'pts.',
					'</td>',
					'<td align="center">',
						Show_PointStr($total_point),'pts.',
					'</td>',
				'</tr>',
			'</tbody>',
		'</table>',
		'<br />',
		'対人戦績',
		'<table border=1>',
			'<tbody>',
				'<tr>',
					'<th bgcolor="#00ff7f">',
						'対戦相手',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'同卓回数',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　捕食　',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　餌食　',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　相性度　',
					'</th>',
				'</tr>',
			$member_str,							// メンバー表示.
			'</tbody>',
		'</table>',
		"※「捕食」は自分が＋で相手が－。「餌食」は相手が＋で自分が－。<br />",
		"※「相性度」は単純に着順が上だったら＋１し、下だったら－１した、その合計。";
		
		// ゲスト分を折りたたみで開く.
		echo
			"<div onclick=\"obj=document.getElementById('menu1').style; obj.display=(obj.display=='none')?'block':'none';\">",
			"<font color=\"#0000ff\"><u><a style=\"cursor:pointer;\">▼ゲスト分も見る</a></u></font>",
			"</div>",
			"<div id=\"menu1\" style=\"display:none;clear:both;\">";
		 
		echo	'<table border=1>',
			'<tbody>',
				'<tr>',
					'<th bgcolor="#00ff7f">',
						'対戦相手',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'同卓回数',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　捕食　',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　餌食　',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　相性度　',
					'</th>',
				'</tr>',
				$guest_str,
			'</tbody>',
		'</table>',
		"</div>",
		"※「ゲスト」は大会出場回数が1回以下の方を指します。<br />",
		'<hr width="100%">';
	}
echo
	'</font>',
	'<a href="../index.html">トップへ</a><br>',
	'</div>',
	'</body>',
	'</html>'
;
?>