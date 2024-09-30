package com.dimtion.shaarlier;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;

import java.util.ArrayList;
import java.util.List;

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
        if (dbHelper != null) {
            db = dbHelper.getReadableDatabase();
        }
    }

    public void wOpen() throws SQLException {
        if (dbHelper != null) {
            db = dbHelper.getWritableDatabase();
        }
    }

    public void close() {
        if (dbHelper != null) {
            dbHelper.close();
        }
    }

    public List<Tag> getAllTags() {
        List<Tag> tags = new ArrayList<>();

        Cursor cursor = db.query(MySQLiteHelper.TABLE_TAGS, allColumns, null, null, null, null, null);
        if (cursor != null) {
            cursor.moveToFirst();
            while (!cursor.isAfterLast()) {
                Tag account = cursorToTag(cursor);
                tags.add(account);
                cursor.moveToNext();
            }
            cursor.close();
        }
        return tags;
    }

    public Tag createTag(ShaarliAccount masterAccount, String value) {
        if (masterAccount == null || value == null) {
            throw new IllegalArgumentException("Invalid input parameters");
        }

        Tag tag = new Tag();
        tag.setMasterAccount(masterAccount);
        tag.setValue(value.trim());

        ContentValues values = new ContentValues();
        values.put(MySQLiteHelper.TAGS_COLUMN_ID_ACCOUNT, masterAccount.getId());
        values.put(MySQLiteHelper.TAGS_COLUMN_TAG, tag.getValue());

        // Check if the tag already exists
        Cursor cursor = db.query(MySQLiteHelper.TABLE_TAGS, allColumns,
                MySQLiteHelper.TAGS_COLUMN_ID_ACCOUNT + " = ? AND " +
                        MySQLiteHelper.TAGS_COLUMN_TAG + " = ?",
                new String[]{String.valueOf(masterAccount.getId()), tag.getValue()}, null, null, null);
        try {
            if (!cursor.moveToFirst()) {
                long insertId = db.insert(MySQLiteHelper.TABLE_TAGS, null, values);
                tag.setId(insertId);
            } else {
                cursor.close();
                return cursorToTag(cursor); // Reuse the existing tag if found
            }
        } finally {
            if (cursor != null) {
                cursor.close();
            }
        }
        return tag;
    }

    private Tag cursorToTag(Cursor cursor) {
        Tag tag = new Tag();
        tag.setId(cursor.getLong(0));
        tag.setMasterAccountId(cursor.getLong(1));
        tag.setValue(cursor.getString(2));
        return tag;
    }

    private void deleteAllTags() {
        db.delete(MySQLiteHelper.TABLE_TAGS, null, null);
    }
}
