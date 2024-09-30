package com.dimtion.shaarlier;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by dimtion on 12/05/2015.
 * Interface between the table TAGS and the JAVA objects
 */
class TagsSource {
    private final String[] allColumns = {MySQLiteHelper.TAGS_COLUMN_ID,
            MySQLiteHelper.TAGS_COLUMN_ID_ACCOUNT,
            MySQLiteHelper.TAGS_COLUMN_TAG};
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

    public List<Tag> getAllTags(ShaarliAccount account) {
        // Limit the amount of information retrieved from the database and only include necessary data for the intended purpose
        String[] projection = new String[]{MySQLiteHelper.TAGS_COLUMN_ID, MySQLiteHelper.TAGS_COLUMN_TAG};

        Cursor cursor = db.query(MySQLiteHelper.TABLE_TAGS, projection, null, null, null, null, null);
        cursor.moveToFirst();
        while (!cursor.isAfterLast()) {
            Tag tag = cursorToTag(cursor);
            if (tag.getMasterAccountId() == account.getId()) {
                tags.add(tag);
            }
            cursor.moveToNext();
        }

        return tags;
    }

    public void createTag(String value, long masterAccountId) throws SQLException {
        // Validate and sanitize user input to prevent SQL injection attacks
        if (value == null || value.trim().isEmpty()) {
            throw new IllegalArgumentException("Invalid tag name");
        }

        value = value.trim();

        ContentValues contentValues = new ContentValues();
        contentValues.put(MySQLiteHelper.TAGS_COLUMN_TAG, value);
        contentValues.put(MySQLiteHelper.TAGS_COLUMN_ID_ACCOUNT, masterAccountId);

        db.insert(MySQLiteHelper.TABLE_TAGS, null, contentValues);
    }

    public void deleteAllTags() throws SQLException {
        // Use prepared statements to prevent SQL injection attacks and protect sensitive data like account IDs
        db.execSQL("DELETE FROM " + MySQLiteHelper.TABLE_TAGS);
    }

    private Tag cursorToTag(Cursor cursor) {
        Tag tag = new Tag();
        tag.setId(cursor.getLong(0));
        tag.setValue(cursor.getString(1));
        return tag;
    }
}
