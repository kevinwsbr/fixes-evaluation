[PYTHON]
import re
from datetime import datetime, timedelta
from dateutil.relativedelta import relativedelta

class DateUtils:
    @staticmethod
    def is_date(date_string):
        date_format = r"%m/%d/%Y"
        return True if re.match(date_format, date_string) else False

    @staticmethod
    def today():
        return datetime.today().strftime("%m/%d/%Y")

    @staticmethod
    def parse_date(date_string):
        date_parts = date_string.split("/")
        month = int(date_parts[0])
        day = int(date_parts[1])
        year = int(date_parts[2])
        return datetime(year, month, day)

    @staticmethod
    def days_between(date1, date2):
        return abs((date1 - date2).days)

    @staticmethod
    def format_date(date):
        return date.strftime("%m/%d/%Y")

    @staticmethod
    def get_future_dates(start_date, num_of_days):
        dates = []
        for i in range(num_of_days):
            start_date += timedelta(days=1)
            dates.append(start_date)
        return dates

    @staticmethod
    def get_past_dates(end_date, num_of_days):
        dates = []
        for i in range(num_of_days):
            end_date -= timedelta(days=1)
            dates.append(end_date)
        return dates[::-1]  # reverse list

    @staticmethod
    def get_future_dates_in_range(start_date, end_date, num_of_days):
        future_dates = []
        for i in range(num_of_days):
            start_date += relativedelta(days=+1)
            if start_date <= end_date:
                future_dates.append(start_date)
        return future_dates

    @staticmethod
    def get_past_dates_in_range(end_date, start_date, num_of_days):
        past_dates = []
        for i in range(num_of_days):
            end_date -= relativedelta(days=+1)
            if end_date >= start_date:
                past_dates.append(end_date)
        return past_dates[::-1]  # reverse list

    @staticmethod
    def is_weekday(date):
        return date.strftime("%A") not in ("Saturday", "Sunday")

    @staticmethod
    def get_next_weekday(date, weekday):
        days_ahead = (date.weekday() - weekday + 7) % 7
        return date + timedelta(days=days_ahead)

    @staticmethod
    def get_prev_weekday(date, weekday):
        days_behind = (weekday - date.weekday()) % 7
        return date - timedelta(days=days_behind)
 [/PYTHON]
[JAVA]
import java.util.Calendar;
import java.util.Date;

public class DateUtils {
    public static boolean isDate(String dateString) {
        // Implement your own logic to validate the date string.
        return true;
    }

    public static String today() {
        Calendar calendar = Calendar.getInstance();
        Date date = calendar.getTime();
        return new SimpleDateFormat("MM/dd/yyyy").format(date);
    }

    public static Date parseDate(String dateString) {
        try {
            return new SimpleDateFormat("MM/dd/yyyy").parse(dateString);
        } catch (ParseException e) {
            // Handle the exception.
            return null;
        }
    }

    public static int daysBetween(Date date1, Date date2) {
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(date1);
        long time1 = calendar.getTimeInMillis();
        calendar.setTime(date2);
        long time2 = calendar.getTimeInMillis();
        return (int) ((time2 - time1) / (1000 * 60 * 60 * 24));
    }

    public static String formatDate(Date date) {
        return new SimpleDateFormat("MM/dd/yyyy").format(date);
    }

    public static List<String> getFutureDates(int numOfDays) {
        Calendar calendar = Calendar.getInstance();
        Date currentDate = calendar.getTime();
        List<String> futureDates = new ArrayList<>();
        for (int i = 0; i < numOfDays; i++) {
            currentDate = addDays(currentDate, 1);
            futureDates.add(new SimpleDateFormat("MM/dd/yyyy").format(currentDate));
        }
        return futureDates;
    }

    public static List<String> getPastDates(int numOfDays) {
        Calendar calendar = Calendar.getInstance();
        Date currentDate = calendar.getTime();
        List<String> pastDates = new ArrayList<>();
        for (int i = 0; i < numOfDays; i++) {
            currentDate = addDays(currentDate, -1);
            pastDates.add(new SimpleDateFormat("MM/dd/yyyy").format(currentDate));
        }
        return pastDates;
    }

    private static Date addDays(Date date, int days) {
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(date);
        calendar.add(Calendar.DATE, days);
        return calendar.getTime();
    }
}
[/JAVA]
[PHP]
<?php
class DateUtils
{
    public static function isDate($date_string) {
        // Implement your own logic to validate the date string.
        return true;
    }

    public static function today() {
        $dt = new DateTime();
        return $dt->format("m/d/Y");
    }

    public static function parseDate($date_string) {
        $dt = DateTime::createFromFormat('m/d/Y', $date_string);
        if ($dt === false) {
            // Handle the exception.
            return null;
        } else {
            return $dt;
        }
    }

    public static function daysBetween(DateTime $date1, DateTime $date2) {
        return $date1->diff($date2)->format("%a");
    }

    public static function formatDate(DateTime $date) {
        return $date->format("m/d/Y");
    }

    public static function getFutureDates($num_of_days) {
        $dates = array();
        for ($i=0; $i<$num_of_days; $i++) {
            $dt = new DateTime(DateUtils::today());
            $dates[] = DateUtils::formatDate($dt->add(new DateInterval('P1D')));
        }
        return $dates;
    }

    public static function getPastDates($num_of_days) {
        $dates = array();
        for ($i=0; $i<$num_of_days; $i++) {
            $dt = new DateTime(DateUtils::today());
            $dates[] = DateUtils::formatDate($dt->sub(new DateInterval('P1D')));
        }
        return array_reverse($dates);
    }
}
[/PHP]
[TESTS]
# Test case 1:
assert(DateUtils::isDate("04/28/2023")); // true
# Test case 2:
assert(!DateUtils::isDate("04/28/202")); // false
# Test case 3:
assert(DateUtils::today() == "05/11/2023"); // true
# Test case 4:
assert(DateUtils::parseDate("04/28/2023")->format("m/d/Y") == "04/28/2023"); // true
# Test case 5:
assert(DateUtils::daysBetween(new DateTime("2023-01-01"), new DateTime("2023-01-15")) == "14"); // true
# Test case 6:
assert(DateUtils::formatDate(new DateTime("2023-01-01")) == "01/01/2023"); // true
# Test case 7:
$dates = DateUtils::getFutureDates(5);
assert($dates[0] == "05/11/2023"); // true
assert($dates[4] == "05/16/2023"); // true
# Test case 8:
$dates = DateUtils::getPastDates(5);
assert($dates[0] == "05/11/2023"); // true
assert($dates[4] == "05/16/2023"); // true
# Test case 9:
$dt = new DateTime("2023-01-01");
$dt->add(new DateInterval('P1D'));
assert($dt->format("m/d/Y") == "01/02/2023"); // true
# Test case 10:
$dt = new DateTime("2023-01-01");
$dt->sub(new DateInterval('P1D'));
assert($dt->format("m/d/Y") == "12/31/2022"); // true
[/TESTS]
