<?php
// ------------------------------.
// 天翔杯 - RTD戦リザルト.
// ------------------------------.
// RTD模擬戦の結果を見せる.

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
	require_once _D_INCLUDE_PATH.'/topen_module.inc';		// オープン戦モジュール.
	
// -------------
// 変数宣言.
// -------------
	
	global $_G_Topen_prefix;					// ルールごとのprefix,
	global $_G_Existence_text;					// ルールごとのありなしテキスト,
	
	// 外部入力の受取.
	if (isset($_REQUEST['id'])) {				// IDの入力がある.
		$member_id = $_REQUEST['id'];
	} else {
		$member_id = 0;							// ないなら初期値.
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
	
	$member_list = Get_TcupMemberList($dbo, 1);	// RTD用.
	if (!$member_list) {
		echo "No Member List...";
		exit();
	}
	
	if ($member_id != 0) {
		// 個人戦績取得.
		$result = Get_PersonnelResult($dbo, $member_id, 1);	// RTD用.
		if (!$result) {
			echo "Illegal Personnel Data";
			exit();
		}
		// 対人戦績.
		$opp = Get_PersonnelOPResult($dbo, $member_id, 1);	// RTD用.
		if (!$opp) {
			echo "Illegal Personnel Data";
			exit();
		}
	}
	
// -------------
// 文言整形.
// -------------
	
	$member_name = $member_list[$member_id]['visible_name'];
	
	if ($member_id != 0) {
		$guest_cnt = 0;
		$member_cnt = 0;
		$guest_str = "";
		$member_str = "";
		$show_color = array(0=>"#FAFFFF", 1=>"#FFFACD");
		// 対戦成績生成.
		foreach ($opp as $key => $data) {
		//	if ($member_list[$data['tcup_member_id']]['is_guest']) {
		//		// ゲスト.
		//		$show_cnt = $guest_cnt++;
		//	} else {
		//		// メンバー
		//		$show_cnt = $member_cnt++;
		//	}
			$show_cnt = $member_cnt++;				// しばらくゲストなし.
			$color_no = $show_cnt % 2;				// 表示用.
			$str = 		
				'<tr>'.
					'<td align="center" bgcolor="'.$show_color[$color_no].'">'.
						'<a href="./total_rtd_result.php?id='.$data['tcup_member_id'].'">'.$member_list[$data['tcup_member_id']]['visible_name'].'</a>'.
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
						'<a href="./vs_rtd_result.php?id1='.$member_id.'&id2='.$data['tcup_member_id'].'">'.Show_PointStr($data['compatible_point'],true).'</a>'.
					'</td>'.
				'</tr>';
			$member_str .= $str;					// しばらくゲストなし.
		//	if ($member_list[$data['tcup_member_id']]['is_guest']) {
		//		// ゲスト.
		//		$guest_str .= $str;
		//	} else {
		//		// メンバー
		//		$member_str .= $str;
		//	}
		}
		// 個人戦績生成.
		// 赤も焼き鳥もないのでnonoしかない.
//		for ($red = 0; $red < 2; $red++) {
//			// 赤のあるなしでぶち抜き.
//			$result_table_str .= 
//								'<tr>'.
//									'<td align="center" rowspan="2" bgcolor="'.$show_color[$red].'">'.
//										$_G_Existence_text[$red].
//									'</td>';
//			for ($yakitori = 0; $yakitori < 2; $yakitori++) {
//				if (0 < $yakitori) {
//					$result_table_str .= '<tr>';																// 1行目以降は改行を入れておく.
//				}
//				$result_table_str .= 
//										// 1,2,3,4,max,min,avg,sum,avgr
//										'<td align="center" bgcolor="'.$show_color[$red].'">'.
//											Show_PointStr($result[$_G_Topen_prefix[$red][$yakitori].'1st_count']).
//										'</td>'.
//										'<td align="center" bgcolor="'.$show_color[$red].'">'.
//											Show_PointStr($result[$_G_Topen_prefix[$red][$yakitori].'2nd_count']).
//										'</td>'.
//										'<td align="center" bgcolor="'.$show_color[$red].'">'.
//											Show_PointStr($result[$_G_Topen_prefix[$red][$yakitori].'3rd_count']).
//										'</td>'.
//										'<td align="center" bgcolor="'.$show_color[$red].'">'.
//											Show_PointStr($result[$_G_Topen_prefix[$red][$yakitori].'4th_count']).
//										'</td>'.
//										'<td align="center" bgcolor="'.$show_color[$red].'">'.
//											Show_PointStr($result[$_G_Topen_prefix[$red][$yakitori].'max_point']).
//										'</td>'.
//										'<td align="center" bgcolor="'.$show_color[$red].'">'.
//											Show_PointStr($result[$_G_Topen_prefix[$red][$yakitori].'min_point']).
//										'</td>'.
//										'<td align="center" bgcolor="'.$show_color[$red].'">'.
//											Show_PointStr($result[$_G_Topen_prefix[$red][$yakitori].'average_point']).
//										'</td>'.
//										'<td align="center" bgcolor="'.$show_color[$red].'">'.
//											Show_PointStr($result[$_G_Topen_prefix[$red][$yakitori].'total_point']).
//										'</td>'.
//										'<td align="center" bgcolor="'.$show_color[$red].'">'.
//											Show_PointStr($result[$_G_Topen_prefix[$red][$yakitori].'average_rank']).
//										'</td>'.
//									'</tr>';
//			}
//		}
		// 最後に合計.
		$result_table_str .= 
							'<tr>'.
								// 1,2,3,4,max,min,avg,avgr,sum
								'<td align="center" bgcolor="#ffc0cb">'.
									Show_PointStr($result['1st_count']).
								'</td>'.
								'<td align="center" bgcolor="#ffc0cb">'.
									Show_PointStr($result['2nd_count']).
								'</td>'.
								'<td align="center" bgcolor="#ffc0cb">'.
									Show_PointStr($result['3rd_count']).
								'</td>'.
								'<td align="center" bgcolor="#ffc0cb">'.
									Show_PointStr($result['4th_count']).
								'</td>'.
								'<td align="center" bgcolor="#ffc0cb">'.
									Show_PointStr($result['max_point']).
								'</td>'.
								'<td align="center" bgcolor="#ffc0cb">'.
									Show_PointStr($result['min_point']).
								'</td>'.
								'<td align="center" bgcolor="#ffc0cb">'.
									Show_PointStr($result['average_point']).
								'</td>'.
								'<td align="center" bgcolor="#ffc0cb">'.
									Show_PointStr($result['total_point']).
								'</td>'.
								'<td align="center" bgcolor="#ffc0cb">'.
									Show_PointStr($result['average_rank']).
								'</td>'.
							'</tr>';
	}
	
// -------------
// 表示.
// -------------
	
echo
	'<html>',
	'<head>',
	  '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">',
	  '<title>天翔杯－RTD模擬戦</title>',
	'</head>',
	'<body bgcolor="#FFFAFA">',
	'<div style="margin-left: 60px; margin-right: 60px">',
		'<br>',
		'<center><FONT size=+3><b>個人戦績-天翔杯RTD模擬戦総合</b></FONT><br></center>',
		'<hr width="100%">',
		'<FONT size=+1>',
		'<center>',
			'<a href="./total_result.php?id='.$member_id.'">天翔杯－オープン戦</a>',
			'&nbsp; &nbsp; &nbsp; &nbsp; ',
			'天翔杯－RTD模擬戦',
			'&nbsp; &nbsp; &nbsp; &nbsp; ',
			'ランキング',
//			'<a href="./ranking.php">ランキング</a>',
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
						'半荘回数',
					'</th>',
				'</tr>',
				'<tr>',
					'<td align="center">',
						$result['attend_count'],'回',
					'</td>',
					'<td align="center">',
						$result['play_count'],'回',
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
					'<th bgcolor="#00ff7f">',
						'　最大pt　',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　最小pt　',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　平均pt　',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　合計pt　',
					'</th>',
					'<th bgcolor="#00ff7f">',
						'　平均着順　',
					'</th>',
				'</tr>',
				$result_table_str,
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
//		echo
//			"<div onclick=\"obj=document.getElementById('menu1').style; obj.display=(obj.display=='none')?'block':'none';\">",
//			"<font color=\"#0000ff\"><u><a style=\"cursor:pointer;\">▼ゲスト分も見る</a></u></font>",
//			"</div>",
//			"<div id=\"menu1\" style=\"display:none;clear:both;\">";
//		 
//		echo	'<table border=1>',
//			'<tbody>',
//				'<tr>',
//					'<th bgcolor="#00ff7f">',
//						'対戦相手',
//					'</th>',
//					'<th bgcolor="#00ff7f">',
//						'同卓回数',
//					'</th>',
//					'<th bgcolor="#00ff7f">',
//						'　捕食　',
//					'</th>',
//					'<th bgcolor="#00ff7f">',
//						'　餌食　',
//					'</th>',
//					'<th bgcolor="#00ff7f">',
//						'　相性度　',
//					'</th>',
//				'</tr>',
//				$guest_str,
//			'</tbody>',
//		'</table>',
//		"</div>",
//		"※「ゲスト」は出場回数が1回以下の方を指します。<br />",
	echo
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