<?php
// ------------------------------.
// 天翔杯 - 大会戦績.
// ------------------------------.
// ユーザAを受け取り、D_TCUP_RESULTからAが参加した大会の戦績を算出する.

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
		$member_id = "";					// ないなら初期値.
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
	
	// 戦績取得.
	if ($member_id != $opp_id) {
		$vs_result = Get_TcupResult($dbo, $member_id );			// 成績を受け取る.
	}
	
// -------------
// 文言整形.
// -------------
	
	$member_name = $member_list[$member_id]['visible_name']."さん";
	
	if ($vs_result) {
		$show_cnt = 0;
		$rank_cnt = 0;								// 順位表示用.
		$show_color = array(0=>"#FAFFFF", 1=>"#FFFACD");
		
		foreach ($vs_result as $tcup_id => $cup_data) {
			foreach ($cup_data as $battle_no => $battle_data) {
				$rank_cnt = 1;						// 初期化.
				$show_cnt++;						// 同卓で1列表示.
				$color_no = $show_cnt % 2;				// 表示用色.
				$show_str .=	'<tr>'.
							'<td align="center" bgcolor="'.$show_color[$color_no].'">'.
								$show_cnt.
							'</td>';
						
				foreach ($battle_data as $table_no => $result_data) {
					foreach ($result_data as $result_cnt => $data) {
						// result_rankで昇順になっている.
						if ($rank_cnt == 1) {
							// 初回は情報表示用文字列作成.
							$show_str .=	'<td bgcolor="'.$show_color[$color_no].'">'.
										$data['tcup_name']." ".					// 大会名.
										Get_TcupBattleNumText($battle_no, $table_no).		// 回戦.
									'</td>';
						}
						$show_str .=	'<td align="center" bgcolor="'.$show_color[$color_no].'">'.
									$member_list[$data['tcup_member_id']]['visible_name'].
								'</td>'.
								'<td align="center" bgcolor="'.$show_color[$color_no].'">'.
									Show_PointStr($data['result_point'], true).		// プラスつける.
								'</td>';
						$rank_cnt++;
					}
				}
				$show_str .=	'</tr>';
			}
		}
	} else {
		$show_str =	$member_name."は".
				"参加したことがありません。";
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
		'<center><FONT size=+3><b>大会戦績</b></FONT><br></center>',
		'<hr width="100%">',
		'<FONT size=+1>',
		'<center>',
			'<a href="./total_result.php?id='.$member_id.'">天翔杯</a>',
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
	if ($vs_result) {
	echo
		$member_name.'の大会成績','<br />',
		'<br />',
		'<table border=1>',
			'<tbody>',
				'<tr>',
					'<th bgcolor="#00ff7f">',
						'回数',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　大会名　',
					'</th>',
					'<th colspan="2" bgcolor="#00ff7f">',
						'　1位　',
					'</th>',
					'<th colspan="2" bgcolor="#00ff7f">',
						'　2位　',
					'</th>',
					'<th colspan="2" bgcolor="#00ff7f">',
						'　3位　',
					'</th>',
					'<th colspan="2" bgcolor="#00ff7f">',
						'　4位　',
					'</th>',
				'</tr>',
			$show_str,							// メンバー表示.
			'</tbody>',
		'</table>';
	} else {
		echo	$show_str;
	}
echo
	'<hr width="100%">',
	'</font>',
	'<a href="./total_result.php?id='.$member_id.'">戻る</a><br>',
	'<a href="../index.html">トップへ</a><br>',
	'</div>',
	'</body>',
	'</html>'
;
?>