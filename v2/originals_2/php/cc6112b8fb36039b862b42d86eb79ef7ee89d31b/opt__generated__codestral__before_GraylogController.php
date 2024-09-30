   private function formatMessage($message) {
       if ($this->timezone) {
           $graylogTime = new DateTime($message['message']['timestamp']);
           $offset = $this->timezone->getOffset($graylogTime);

           $timeInterval = DateInterval::createFromDateString((string)$offset . 'seconds');
           $graylogTime->add($timeInterval);
           $displayTime = $graylogTime->format('Y-m-d H:i:s');
       } else {
           $displayTime = $message['message']['timestamp'];
       }

       $device = $this->deviceFromSource(htmlspecialchars($message['message']['source']));
       $level = htmlspecialchars($message['message']['level']) ?? '';
       $facility = htmlspecialchars($message['message']['facility']) ?? '';

       return [
           'severity'  => $this->severityLabel($level),
           'timestamp' => $displayTime,
           'source'    => $device ? Url::deviceLink($device) : htmlspecialchars($message['message']['source']),
           'message'   => htmlspecialchars($message['message']['message']) ?? '',
           'facility'  => is_numeric($facility) ? "($facility) " . __("syslog.facility.$facility") : $facility,
           'level'     => (is_numeric($level) && $level >= 0) ? "($level) " . __("syslog.severity.$level") : $level,
       ];
   }
   