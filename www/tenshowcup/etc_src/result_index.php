<?php
// ------------------------------.
// 天翔杯 - 結果早見表.
// ------------------------------.
// 大会結果を一覧で早見する表.

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
	
	// 外部入力はなし.
	$member_link = "../personnel/total_result.php?id=";
	$result_page = "/result.html";
	$result_link = array(
				1 => "../src",
				2 => "../src_sp",
			);
	
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
	
	// 大会一覧取得.
	$cup_list = Get_TcupList($dbo);				// 大会全部.
	if (!$cup_list) {
		echo "Illegal cup list";
		exit();
	}
	// 大会入賞者一覧.
	$prizewinner_list = Get_TcupPrizewinner($dbo);		// 大会入賞者取得.
	if (!$prizewinner_list) {
		echo "Illegal prizewinnder list";
		exit();
	}
	// 役満取得者.
	$yakuman_getter_list = Get_TcupYakumanGetter($dbo);	// 役満取得者リスト.
	if (!$yakuman_getter_list) {
		echo "Illegal yakuman getter";
		exit();
	}
//	// 大会総参加者数.
//	$attendee_count = Get_TcupAttendeeCount($dbo);		// 大会総参加者数.
//	if (!$attendee_count) {
//		echo "Illegal attendee count";
//		exit();
//	}
	
// -------------
// 文言整形.
// -------------
	
	$fontsize_str = array(1=>"+3", 2=>"+2", 3=>"+1");
	$tablecolor_str = array(1=>"#FFFF00", 2=>"#a9a9a9", 3=>"#8b4513");
	$rowcolor_str = array(0=>"#FAFFFF", 1=>"#FFFACD");
	$rank_icon = array(1=>"./1.ico", 2=>"./2.ico", 3=>"./3.ico", 4=>"./3.ico", 5=>"./5.ico");
	
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
		'<center><FONT size="+3"><b>大会戦績早見表</b></FONT><br></center>',
		'<hr width="100%">',
		'<center>',
			'戦績',
			'&nbsp; &nbsp; &nbsp; &nbsp; ',
			'<a href="./attend_count.php">参加回数</a>',
		'</center>',
		'<hr width="100%">';
	// 戦績早見表.
	echo
		// 見出し
		'<table border=1>',
			'<tbody>',
			'<tr bgcolor="#00ff7f">',
				'<th align="center">',
					'No.',
				'</th>',
				'<th align="center">',
					'大会名',
				'</th>',
				'<th align="center">',
					'開催日',
				'</th>',
				'<th align="center">',
					'参加人数',
				'</th>',
				'<th align="center" colspan="2">',
					'優勝',
				'</th>',
				'<th align="center" colspan="2">',
					'準優勝',
				'</th>',
				'<th align="center" colspan="2">',
					'3位',
				'</th>',
				'<th align="center" colspan="2">',
					'4位',
				'</th>',
				'<th align="center" colspan="2">',
					'5位',
				'</th>',
				'<th align="center">',
					'備考',
				'</th>',
			'</tr>';
	foreach ($cup_list as $tcup_id => $tcup_data) {
		if ($prizewinner_list[$tcup_id]) {
			// 開催済み.
			$page_link = $result_link[$tcup_data['tcup_type']].$tcup_data['tcup_serial_id'].$result_page;
			$cup_name = '<a href="'.$page_link.'">'.($tcup_data['tcup_name']).'</a>';
		} else {
			// まだ.
			$cup_name = ($tcup_data['tcup_name']);
		}
	echo	'<tr bgcolor="',$rowcolor_str[($tcup_id%2)],'">',
			'<td align="center">',	// 番号
				$tcup_id,
			'</td>',
			'<td align="center">',	// 名前
				$cup_name,
			'</td>',
			'<td align="center">',	// 開催日.
				date("Y年m月d日", strtotime($tcup_data['open_date'])),
			'</td>',
			'<td align="center">',	// 人数.
				$tcup_data['member_count'],"人",
			'</td>';
		// 成績.
		if ($prizewinner_list[$tcup_id]) {
			foreach ($prizewinner_list[$tcup_id] as $result_rank => $member_data) {
				// 通常と最強位で表示を分ける.
				$member_page =	'<a href="'.$member_link.$member_data['tcup_member_id'].'">'.
						$member_data['visible_name'].
						'</a>';
				if ($tcup_data['tcup_type'] == 1) {
					// 通常.
				echo	'<td align="center">',
						// まずアイコン.
						'<img src="',$rank_icon[$member_data['tcup_result_rank']],'">',
					'</td>',
					'<td align="center">',
						// 名前.
						$member_page,
					'</td>';
				} else if ($tcup_data['tcup_type'] == 2) {
					// 最強位.
					if ($member_data['tcup_result_rank'] == 1) {
						// 1位だけアイコン.
					echo	'<td align="center">',
							// 1位だけアイコン.
							'<img src="./s.ico">',
						'</td>',
						'<td align="center">',
							// 名前.
							$member_page,
						'</td>';
					} else {
						// それ以外は名前だけ.
					echo	'<td align="center" colspan="2">',
							// 名前.
							$member_page,
						'</td>';
						
					}
				}
			}
		} else {
			// 未確定.
		echo	'<td align="center" colspan="10">',
				// 更新待ち.
				"未確定",
			'</td>';
		}
		// 備考で役満.
		if (!$yakuman_getter_list[$tcup_id]) {
			// いない.
		echo	'<td align="center">',
				"特になし",
			'</td>';
		} else {
			// いる.
		echo	'<td>';
			foreach ($yakuman_getter_list[$tcup_id] as $getter_data) {
			echo	$getter_data['tcup_yakuman_name'],
				"：",
				'<a href="'.$member_link.$getter_data['tcup_member_id'].'">'.
				$getter_data['visible_name'],
				'</a>',
				"<br>";
			}
		echo	'</td>';
		}
	echo	'</tr>';
	}
	echo
			'</tbody>',
		'</table>',
		'<p></p>';
echo
	'<hr width="100%">';
echo
	'</font>',
	'<a href="../index.html">トップへ</a><br>',
	'</div>',
	'</body>',
	'</html>'
;
?>