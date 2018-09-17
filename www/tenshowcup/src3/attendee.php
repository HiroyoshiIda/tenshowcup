<?php
// ------------------------------.
// 天翔杯 - 参加者一覧.
// ------------------------------.
// 

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
	$tcup_id = 3;
	$tcup_type = 1;
	
	if (!is_numeric($tcup_id)) {
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
	
	$attendee_list = Get_TcupAttendeeList($dbo, $tcup_id, $tcup_type);
	if (!$attendee_list) {
		echo "No Member List...";
		exit();
	}
	
// -------------
// 文言整形.
// -------------
	
	$member_count = 0;
	
// -------------
// 表示.
// -------------
	
echo
	'<html>',
	'<head>',
	  '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">',
	  '<title>天翔杯-参加者</title>',
	'</head>',
	'<body bgcolor="#FAFFFF">',
		'<font face="HG正楷書体-PRO" size="6">参加者一覧</font><font color="#993300" size="+1">　</font>';
	
foreach ($attendee_list as $key => $data) {
	// 参加／実績系文言抽出.
	$fullname_str = Show_FullnameStr($data);
	$attend_str = Show_AttendStr($data);
	$achievement_str = Show_AchievementStr($data);
	$attend_comment = Show_AttendCommentStr($data);
	$member_count++;
	
	// レイアウト.
	if (($member_count % 2) == 0) {
		$tbody_border = "";
		$name_str =	'<td width="150">'.
					'名前'.
				'</td>'.
				'<td width="600">'.
					$fullname_str.
				'</td>'.
				'<td rowspan="5" width="240" height="240" align="center">'.
					'<img title="画像はイメージです" src="./'.$data['tcup_member_img'].'.jpg">'.
				'</td>';
	} else {
		$tbody_border = ' border="1"';
		$name_str = 	'<td rowspan="5" width="240" height="240" align="center">'.
					'<img title="画像はイメージです" src="./'.$data['tcup_member_img'].'.jpg">'.
				'</td>'.
				'<td width="150">'.
					'名前'.
				'</td>'.
				'<td width="600">'.
					$fullname_str.
				'</td>';
	}
	echo
		'<table border="1">',
			'<tbody'.$tbody_border.'>',
				'<tr>',
					$name_str,
				'</tr>',
				'<tr>',
					'<td width="150">',
						'表示名',
					'</td>',
					'<td width="600">',
						$data['visible_name'],
					'</td>',
				'</tr>',
				'<tr>',
					'<td width="150">',
						'出場回数',
					'</td>',
					'<td width="600">',
						$attend_str,
					'</td>',
				'</tr>',
				'<tr>',
					'<td width="150">',
						'実績',
					'</td>',
					'<td width="600">',
						$achievement_str,
					'</td>',
				'</tr>',
				'<tr>',
					'<td>',
						'大会に向けて一言',
					'</td>',
					'<td>',
						$attend_comment,
					'</td>',
				'</tr>',
			'</tbody>',
		'</table>',
		'<p></p>';
}

if (!array_key_exists(1, $attendee_list)) {
	// 井田がいない場合には補欠で待機していることを示しておく.
	$tbody_border = "";
	$name_str =	'<td width="150">'.
				'名前'.
			'</td>'.
			'<td width="600">'.
				'井田'.
			'</td>'.
			'<td rowspan="2" width="240" height="240" align="center">'.
				'<img title="画像はイメージです" src="./ida.jpg">'.
			'</td>';
	
	echo
		'<table border="1">',
			'<tbody'.$tbody_border.'>',
				'<tr>',
					'井田',
				'</tr>',
				'<tr>',
					'<td>',
						'大会に向けて一言',
					'</td>',
					'<td>',
						"主催者です。<br />",
						"今回は補欠で待機しております。<br />",
						"どうぞ楽しんでいってください。",
					'</td>',
				'</tr>',
			'</tbody>',
		'</table>';
}
	
echo
	'<hr width="100%">',
	'<a href="../index.html">トップへ</a><br>',
	'</body>',
	'</html>'
;
?>