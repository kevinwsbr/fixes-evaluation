import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import java.util.ArrayList;
import java.util.List;

class TagsSource {
    private final String[] allColumns = {MySQLiteHelper.TAGS_COLUMN_ID, MySQLiteHelper.TAGS_COLUMN_ID_ACCOUNT, MySQLiteHelper.TAGS_COLUMN_TAG};
    private final MySQLiteHelper dbHelper;
    private SQLiteDatabase db;

    public TagsSource(Context context) {
        dbHelper = new MySQLiteHelper(context);
    }

    public void rOpen() throws SQLException {
        db = dbHelper.getReadableDatabase();
    }

    public void wOpen() throws SQLException {
        db = dbHelper.getWritableDatabase();
    }

    public void close() {
        dbHelper.close();
    }

    public List<Tag> getAllTags() {
        List<Tag> tags = new ArrayList<>();
        Cursor cursor = null;
        try {
            cursor = db.query(MySQLiteHelper.TABLE_TAGS, allColumns, null, null, null, null, null);
            if (cursor.moveToFirst()) {
                while (!cursor.isAfterLast()) {
                    Tag account = cursorToTag(cursor);
                    tags.add(account);
                    cursor.moveToNext();
                }
            }
        } finally {
            if (cursor != null) {
                cursor.close();
            }
        }
        return tags;
    }

    public Tag createTag(ShaarliAccount masterAccount, String value) {
        ContentValues values = new ContentValues();
        values.put(MySQLiteHelper.TAGS_COLUMN_ID_ACCOUNT, masterAccount.getId());
        values.put(MySQLiteHelper.TAGS_COLUMN_TAG, value.trim());

        String[] selectionArgs = {String.valueOf(masterAccount.getId()), value.trim()};
        Cursor cursor = null;
        try {
            cursor = db.query(MySQLiteHelper.TABLE_TAGS, allColumns, MySQLiteHelper.TAGS_COLUMN_ID_ACCOUNT + " = ? AND " + MySQLiteHelper.TAGS_COLUMN_TAG + " = ?", selectionArgs, null, null, null);
            if (cursor.moveToFirst()) {
                return cursorToTag(cursor);
            } else {
                long insertId = db.insert(MySQLiteHelper.TABLE_TAGS, null, values);
                Tag tag = new Tag();
                tag.setId(insertId);
                tag.setMasterAccount(masterAccount);
                tag.setValue(value.trim());
                return tag;
            }
        } catch (SQLException e) {
            // Handle or log exception properly
            return null;
        } finally {
            if (cursor != null) {
                cursor.close();
            }
        }
    }

    private Tag cursorToTag(Cursor cursor) {
        // Assuming you have column indices for ID, ACCOUNT_ID and TAG
        long id = cursor.getLong(COLUMN_INDEX_ID);
        long accountId = cursor.getLong(COLUMN_INDEX_ACCOUNT_ID);
        String tag = cursor.getString(COLUMN_INDEX_TAG);

        Tag newTag = new Tag();
        newTag.setId(id);
        // Set other properties based on your requirement

        return newTag;
    }
}
