[PYTHON]
class RedmineHelper:
    def self.instance(context):
        if not context.respond_to?(:h)
            context.extend(self)
        end
        return context
[/PYTHON]
[JAVA]
package utils;

import org.apache.commons.lang.StringEscapeUtils;
import org.joda.time.format.DateTimeFormat;
import org.joda.time.format.DateTimeFormatter;

public class RedmineHelper {
    public static String formatDate(String date, String pattern) {
        DateTimeFormatter formatter = DateTimeFormat.forPattern(pattern);
        return formatter.print(date);
    }

    public static String formatDuration(long seconds) {
        if (seconds < 0) {
            return "0";
        } else {
            long days = seconds / 86400;
            long hours = (seconds % 86400) / 3600;
            long minutes = (seconds % 3600) / 60;
            long remainingSeconds = seconds % 60;

            String result = "";
            if (days > 0) {
                result += days + "d ";
            }
            if (hours > 0) {
                result += hours + "h ";
            }
            if (minutes > 0) {
                result += minutes + "m ";
            }
            result += remainingSeconds + "s";
            return result;
        }
    }

    public static String formatDuration(long seconds, boolean withTime) {
        if (!withTime || seconds < 3600) {
            return formatDuration(seconds);
        } else {
            long hours = (seconds % 86400) / 3600;
            long minutes = (seconds % 3600) / 60;
            long remainingSeconds = seconds % 60;

            String result = "";
            result += hours + "h ";
            result += minutes + "m ";
            result += remainingSeconds + "s";
            return result;
        }
    }

    public static String formatDuration(long seconds, boolean withTime, int precision) {
        if (!withTime || seconds < 3600) {
            return formatDuration(seconds);
        } else {
            long hours = (seconds % 86400) / 3600;
            long minutes = (seconds % 3600) / 60;
            long remainingSeconds = seconds % 60;

            String result = "";
            result += hours + "h ";
            result += minutes + "m ";
            result += remainingSeconds + "s";
            return result;
        }
    }
}
[/JAVA]
[PHP]
<?php

namespace Helpers;

use Config\Config as AppConfig;
use DateTime;
use NumberFormatter;

class RedmineHelper
{
    private static $instance;

    public static function getInstance()
    {
        if (self::$instance == null) {
            self::$instance = new RedmineHelper();
        }

        return self::$instance;
    }

    public function formatDate($date, $format = 'F j, Y')
    {
        return DateTime::createFromFormat('Y-m-d', $date)->format($format);
    }

    public function formatDuration($seconds)
    {
        if ($seconds < 0) {
            return "0";
        } else {
            $duration = [];

            // Days
            $days = floor($seconds / (24 * 60 * 60));
            if ($days > 0) {
                $duration[] = sprintf("%d day%s", $days, $days == 1 ? '' : 's');
            }

            // Hours
            $hours = floor(($seconds - ($days * 24 * 60 * 60)) / (60 * 60));
            if ($hours > 0) {
                $duration[] = sprintf("%d hour%s", $hours, $hours == 1 ? '' : 's');
            }

            // Minutes
            $minutes = floor(($seconds - ($days * 24 * 60 * 60) - ($hours * 60 * 60)) / (60));
            if ($minutes > 0) {
                $duration[] = sprintf("%d minute%s", $minutes, $minutes == 1 ? '' : 's');
            }

            // Seconds
            $remainingSeconds = floor($seconds - ($days * 24 * 60 * 60) - ($hours * 60 * 60) - ($minutes * 60));
            if ($remainingSeconds > 0) {
                $duration[] = sprintf("%d second%s", $remainingSeconds, $remainingSeconds == 1 ? '' : 's');
            }

            return implode(' and ', $duration);
        }
    }
}

[/PHP]
[PERL]
package Redmine::Helper;
use DateTime;

sub format_date {
    my ($self, $date, $format) = @_;
    return DateTime->create_from_format('Y-m-d', $date)->strftime($format);
}

sub format_duration {
    my ($self, $seconds) = @_;
    if ($seconds < 0) {
        return "0";
    } else {
        my %parts;

        # Days
        $parts{d} = int($seconds / (24 * 60 * 60));
        $seconds -= $parts{d} * (24 * 60 * 60);

        # Hours
        $parts{h} = int($seconds / (60 * 60));
        $seconds -= $parts{h} * (60 * 60);

        # Minutes
        $parts{m} = int($seconds / (60));
        $seconds -= $parts{m} * (60);

        # Seconds
        $remaining_seconds = $seconds % 60;
        if ($remaining_seconds > 0) {
            $parts{s} = int($remaining_seconds);
        }

        return sprintf("%dd %dh %dm %ds", @parts{qw(d h m s)});
    }
}
1;
[/PERL]
[SCALA]
package utils.RedmineHelper
import java.text.SimpleDateFormat
import java.util.Date
object RedmineHelper {
  def formatDate(date: Date, pattern: String): String = {
    val dateFormat = new SimpleDateFormat(pattern)
    dateFormat.format(date)
  }
  def formatDuration(seconds: Int): String = {
    if (seconds < 0) {
      "0"
    } else {
      var duration = ""
      // Days
      val days = seconds / (24 * 60 * 60)
      if (days > 0) {
        duration += s"$days day${if (days > 1) "s" else ""} "
      }
      // Hours
      val hours = (seconds - days * 24 * 60 * 60) / (60 * 60)
      if (hours > 0) {
        duration += s"$hours hour${if (hours > 1) "s" else ""} "
      }
      // Minutes
      val minutes = (seconds - days * 24 * 60 * 60 - hours * 60 * 60) / (60)
      if (minutes > 0) {
        duration += s"$minutes minute${if (minutes > 1) "s" else ""} "
      }
      // Seconds
      val remainingSeconds = seconds - days * 24 * 60 * 60 - hours * 60 * 60 - minutes * 60
      if (remainingSeconds > 0) {
        duration += s"$remainingSeconds second${if (remainingSeconds > 1) "s" else ""}"
      }
      duration
    }
  }
}
[/SCALA]
