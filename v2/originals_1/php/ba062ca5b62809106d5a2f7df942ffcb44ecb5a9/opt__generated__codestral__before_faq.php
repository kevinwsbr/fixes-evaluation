if($stx) {
    $sql_search = " AND ( INSTR(fa_subject, ?) > 0 OR INSTR(fa_content, ?) > 0 ) ";
}

// ...

$sql = "SELECT COUNT(*) AS cnt FROM {$g5['faq_table']} WHERE fm_id = ? $sql_search";
if($stx) {
    $stmt = sql_query($sql, array($fm_id, $stx, $stx));
} else {
    $stmt = sql_query($sql, array($fm_id));
}
$total = sql_fetch_array($stmt);
// ...

$sql = "SELECT * FROM {$g5['faq_table']} WHERE fm_id = ? $sql_search ORDER BY fa_order , fa_id LIMIT ?, ?";
if($stx) {
    $result = sql_query($sql, array($fm_id, $stx, $stx, $from_record, $page_rows));
} else {
    $result = sql_query($sql, array($fm_id, $from_record, $page_rows));
}
