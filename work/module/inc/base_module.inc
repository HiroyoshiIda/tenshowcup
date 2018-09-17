<?php
// base_module.

require_once _D_CLASS_PATH.'/DBObject.class.php';
require_once _D_TWITTER_AUTH_PATH."/twitteroauth.php";

/**
 * DB接続
 * 
 * @param		なし
 * @return 	ret	[Object]	DBClass.(NULLで失敗)
 */
function Connect_DB()
{
	$dbo = new DBObject();
	$dbo->connect( _D_DB_SERVER, _D_DB_USER, _D_DB_PSWD, _D_DB_NAME, 'utf8' );
	
	return $dbo;
}

/**
 * TwiObject生成
 * 
 * @param		なし
 * @return 	ret	[Object]	TwitterOAuthObject.(NULLで失敗)
 */
function Connect_Tw()
{
	$to = new TwitterOAuth(_D_TW_CON_KEY,_D_TW_CON_SEC,_D_TW_ACS_TOKEN,_D_TW_ACS_TOKEN_SEC);
	
	return $to;
}

/**
 * クエリ発行
 * 
 * @param	dbo	[Object]	DBObject
 * @param	sql	[str]		SQL文字列
 * @return 	ret	[Object]	DBClass.(NULLで失敗)
 */
function Execute_Query( $dbo, $SQL )
{
	$dbo->query( $SQL );
	if (!empty($dbo->error)) {
		// 何か失敗.
		echo $dbo->error.$SQL;
		return NULL;
	}
	// 成功.
	return TRUE;
}

/**
 * TwitterへPOST
 * 
 * @param	to	[Object]	TwitterObject
 * @param	text	[str]		投稿文字列
 * @return 	ret	[str]		結果セット.(XMLで帰ってくる)
 */
function Post_Tweet( $to, $text )
{
	$post_array = array(
		'status' => $text,
	);
	
	$req = $to->OAuthRequest(_D_TW_POST_URL, "POST", $post_array);
	
	// 結果を返す.
	return $req;
}

?>
