<?php
// ------------------------------.
// 天翔杯 - ranking.
// ------------------------------.
// D_TCUP_RESULTを総計して、ランキング.

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
	
	// ランキングは入力なし.
	
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
	
	// 瞬間最大風速取得.
	$point_desc_ranking = Get_TcupPointRanking($dbo, 1);	// 降順.
	if (!$point_desc_ranking) {
		echo "Illegal point desc";
		exit();
	}
	$point_asc_ranking = Get_TcupPointRanking($dbo, 2);	// 昇順.
	if (!$point_asc_ranking) {
		echo "Illegal point asc";
		exit();
	}
	// 予選戦績.
	$prepoint_desc_ranking = Get_TcupPrePointRanking($dbo, 1);	// 降順.
	if (!$prepoint_desc_ranking) {
		echo "Illegal point desc";
		exit();
	}
	$prepoint_asc_ranking = Get_TcupPrePointRanking($dbo, 2);	// 昇順.
	if (!$prepoint_asc_ranking) {
		echo "Illegal point asc";
		exit();
	}
	// 本戦戦績.
	$finalpoint_desc_ranking = Get_TcupFinalPointRanking($dbo, 1);	// 降順.
	if (!$finalpoint_desc_ranking) {
		echo "Illegal point desc";
		exit();
	}
	$finalpoint_asc_ranking = Get_TcupFinalPointRanking($dbo, 2);	// 昇順.
	if (!$finalpoint_asc_ranking) {
		echo "Illegal point asc";
		exit();
	}
	// 決勝卓戦績.
	$winnerspoint_desc_ranking = Get_TcupWinnersPointRanking($dbo, 1);	// 降順.
	if (!$winnerspoint_desc_ranking) {
		echo "Illegal point desc";
		exit();
	}
	$winnerspoint_asc_ranking = Get_TcupWinnersPointRanking($dbo, 2);	// 昇順.
	if (!$winnerspoint_asc_ranking) {
		echo "Illegal point asc";
		exit();
	}
	
// -------------
// 文言整形.
// -------------
	
	$fontsize_str = array(1=>"+3", 2=>"+2", 3=>"+1");
	$tablecolor_str = array(1=>"#FFFF00", 2=>"#a9a9a9", 3=>"#8b4513");
	$rowcolor_str = array(1=>"#FFFACD", 2=>"#e6e6fa", 3=>"#FAFFFF");
	
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
		'<center><FONT size="+3"><b>個人戦績-ランキング</b></FONT><br></center>',
		'<hr width="100%">',
		'<FONT size="+1">',
		'<center>',
			'<a href="./total_result.php">天翔杯</a>',
			'&nbsp; &nbsp; &nbsp; &nbsp; ',
			'<a href="./total_sp_result.php">最強位</a>',
			'&nbsp; &nbsp; &nbsp; &nbsp; ',
			'ランキング',
		'</center>',
		'<hr width="100%">';
	// 最高.
	echo
		'瞬間最大獲得ポイント',
		'<table border=1>',
			'<tbody>';
	foreach ($point_desc_ranking as $key => $data) {
	echo	'<tr bgcolor="',$rowcolor_str[$key],'">',
			'<td bgcolor="',$tablecolor_str[$key],'" align="center" width="64">',
				'<font size="',$fontsize_str[$key],'">',$key,'位','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',Show_PointStr($data['result_point']),'pts.','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',$data['visible_name'],'</font>',
			'</td>',
			'<td align="center" width="192">',
				$data['tcup_name']," ",
				"第",$data['battle_no'],"回戦",
			'</td>',
		'</tr>';
	}
	echo
			'</tbody>',
		'</table>',
		'<p></p>';
	// 最低.
	echo
		'瞬間最低獲得ポイント',
		'<table border=1>',
			'<tbody>';
	foreach ($point_asc_ranking as $key => $data) {
	echo	'<tr bgcolor="',$rowcolor_str[$key],'">',
			'<td bgcolor="',$tablecolor_str[$key],'" align="center" width="64">',
				'<font size="',$fontsize_str[$key],'">',$key,'位','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',Show_PointStr($data['result_point']),'pts.','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',$data['visible_name'],'</font>',
			'</td>',
			'<td align="center" width="192">',
				$data['tcup_name']," ",
				"第",$data['battle_no'],"回戦",
			'</td>',
		'</tr>';
	}
	echo
			'</tbody>',
		'</table>',
		'<p></p>';
	// 予選最大.
	echo
		'予選合計最大ポイント',
		'<table border=1>',
			'<tbody>';
	foreach ($prepoint_desc_ranking as $key => $data) {
	echo	'<tr bgcolor="',$rowcolor_str[$key],'">',
			'<td bgcolor="',$tablecolor_str[$key],'" align="center" width="64">',
				'<font size="',$fontsize_str[$key],'">',$key,'位','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',Show_PointStr($data['total_point']),'pts.','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',$data['visible_name'],'</font>',
			'</td>',
			'<td align="center" width="192">',
				$data['tcup_name']," ",
			'</td>',
		'</tr>';
	}
	echo
			'</tbody>',
		'</table>',
		'<p></p>';
	// 予選最小.
	echo
		'予選合計最小ポイント',
		'<table border=1>',
			'<tbody>';
	foreach ($prepoint_asc_ranking as $key => $data) {
	echo	'<tr bgcolor="',$rowcolor_str[$key],'">',
			'<td bgcolor="',$tablecolor_str[$key],'" align="center" width="64">',
				'<font size="',$fontsize_str[$key],'">',$key,'位','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',Show_PointStr($data['total_point']),'pts.','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',$data['visible_name'],'</font>',
			'</td>',
			'<td align="center" width="192">',
				$data['tcup_name']," ",
			'</td>',
		'</tr>';
	}
	echo
			'</tbody>',
		'</table>',
		'<p></p>';
	// 本戦最大.
	echo
		'本戦合計最大ポイント',
		'<table border=1>',
			'<tbody>';
	foreach ($finalpoint_desc_ranking as $key => $data) {
	echo	'<tr bgcolor="',$rowcolor_str[$key],'">',
			'<td bgcolor="',$tablecolor_str[$key],'" align="center" width="64">',
				'<font size="',$fontsize_str[$key],'">',$key,'位','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',Show_PointStr($data['total_point']),'pts.','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',$data['visible_name'],'</font>',
			'</td>',
			'<td align="center" width="192">',
				$data['tcup_name']," ",
			'</td>',
		'</tr>';
	}
	echo
			'</tbody>',
		'</table>',
		'<p></p>';
	// 本戦最小.
	echo
		'本戦合計最小ポイント',
		'<table border=1>',
			'<tbody>';
	foreach ($finalpoint_asc_ranking as $key => $data) {
	echo	'<tr bgcolor="',$rowcolor_str[$key],'">',
			'<td bgcolor="',$tablecolor_str[$key],'" align="center" width="64">',
				'<font size="',$fontsize_str[$key],'">',$key,'位','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',Show_PointStr($data['total_point']),'pts.','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',$data['visible_name'],'</font>',
			'</td>',
			'<td align="center" width="192">',
				$data['tcup_name']," ",
			'</td>',
		'</tr>';
	}
	echo
			'</tbody>',
		'</table>',
		'<p></p>';
	// 決勝卓最大.
	echo
		'決勝卓合計最大ポイント',
		'<table border=1>',
			'<tbody>';
	foreach ($winnerspoint_desc_ranking as $key => $data) {
	echo	'<tr bgcolor="',$rowcolor_str[$key],'">',
			'<td bgcolor="',$tablecolor_str[$key],'" align="center" width="64">',
				'<font size="',$fontsize_str[$key],'">',$key,'位','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',Show_PointStr($data['total_point']),'pts.','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',$data['visible_name'],'</font>',
			'</td>',
			'<td align="center" width="192">',
				$data['tcup_name']," ",
			'</td>',
		'</tr>';
	}
	echo
			'</tbody>',
		'</table>',
		'<p></p>';
	// 決勝卓最小.
	echo
		'決勝卓合計最小ポイント',
		'<table border=1>',
			'<tbody>';
	foreach ($winnerspoint_asc_ranking as $key => $data) {
	echo	'<tr bgcolor="',$rowcolor_str[$key],'">',
			'<td bgcolor="',$tablecolor_str[$key],'" align="center" width="64">',
				'<font size="',$fontsize_str[$key],'">',$key,'位','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',Show_PointStr($data['total_point']),'pts.','</font>',
			'</td>',
			'<td align="center" width="160">',
				'<font size="',$fontsize_str[$key],'">',$data['visible_name'],'</font>',
			'</td>',
			'<td align="center" width="192">',
				$data['tcup_name']," ",
			'</td>',
		'</tr>';
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