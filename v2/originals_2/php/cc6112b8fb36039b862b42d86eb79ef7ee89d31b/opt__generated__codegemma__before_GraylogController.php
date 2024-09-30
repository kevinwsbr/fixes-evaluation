```php
private function formatMessage($message)
{
    if ($this->timezone) {
        $graylogTime = new DateTime($message['message']['timestamp']);
        $offset = $this->timezone->getOffset($graylogTime);

        $timeInterval = DateInterval::createFromDateString((string) $offset . 'seconds');
        $graylogTime->add($timeInterval);
        $displayTime = $graylogTime->format('Y-m-d H:i:s');
    } else {
        $displayTime = $message['message']['timestamp'];
    }

    $device = $this->deviceFromSource($message['message']['source']);
    $level = $message['message']['level'] ?? '';
    $facility = $message['message']['facility'] ?? '';

    return [
        'severity'  => $this->severityLabel($level),
        'timestamp' => $displayTime,
        'source'    => $device ? Url::deviceLink($device) : $this->sanitizeInput($message['message']['source']),
        'message'   => $this->sanitizeInput($message['message']['message'] ?? ''),
        'facility'  => is_numeric($facility) ? "($facility) " . __("syslog.facility.$facility") : $facility,
        'level'     => (is_numeric($level) && $level >= 0) ? "($level) " . __("syslog.severity.$level") : $level,
    ];
}

private function sanitizeInput($input)
{
    return htmlspecialchars($input, ENT_QUOTES, 'UTF-8');
}
