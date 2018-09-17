<?php
// ------------------------------.
// 天翔杯 - 参加回数早見表.
// ------------------------------.
// 大会参加回数を一覧で早見する表.

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
	
//	// 実績取得
	$attendee_list = Get_TcupAttendeeData2($dbo);
	if (!$attendee_list) {
		echo "Illegal Achieve Data";
		exit();
	}
	
// -------------
// 文言整形.
// -------------
	
	$fontsize_str = array(1=>"+3", 2=>"+2", 3=>"+1");
	$tablecolor_str = array(1=>"#FFFF00", 2=>"#a9a9a9", 3=>"#8b4513");
	$rowcolor_str = array(0=>"#FAFFFF", 1=>"#FFFACD");
	$show_count = 0;
	
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
			'<a href="./result_index.php">戦績</a>',
			'&nbsp; &nbsp; &nbsp; &nbsp; ',
			'参加回数',
		'</center>',
		'<hr width="100%">';
	// 戦績早見表.
	echo
		// 見出し
		'<center>',
		'<table border=1>',
			'<tbody>',
			'<tr bgcolor="#00ff7f">',
				'<th align="center">',
					'大会参加回数',
				'</th>',
				'<th align="center">',
					'参加者名',
				'</th>',
				'<th align="center">',
					'実績',
				'</th>',
			'</tr>';
	foreach ($attendee_list as $attend_count => $member_list) {
		$same_count = 0;													// 同着チェッカー初期化.
		echo	'<tr bgcolor="',$rowcolor_str[($show_count%2)],'">',
				'<td align="center" rowspan="',count($member_list),'">',	// ぶち抜き件数はここで決める.
					$attend_count,'回',
				'</td>';
		foreach ($member_list as $member_id => $member_data) {
			$member_page =	'<a href="'.$member_link.$member_data['tcup_member_id'].'">'.
					$member_data['visible_name'].
					'</a>';
			if (0 < $same_count) {
				echo	'<tr bgcolor="',$rowcolor_str[($show_count%2)],'">';	// 同着は同色.
			}
			echo	'<td align="center">',
						// 名前.
						$member_page,
					'</td>',
					'<td>',
						// 実績.
						Show_AchievementStr($member_data),
					'</td>',
					'</tr>';
			$same_count++;													// 同回数チェッカーのインクリメント.
		}
		$show_count++;														// 件数増加.
	}
	echo
			'</tbody>',
		'</table>',
		'</center>',
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