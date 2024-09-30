[PYTHON]
import os
from urllib.request import urlretrieve
from bs4 import BeautifulSoup as BS

def download_images(soup):
    for img in soup.find_all('img'):
        src = img.get('src')
        if src and src.startswith('http'):
            filename = os.path.basename(src)
            print("Downloading image {}...".format(filename))
            urlretrieve(src, filename)

def main():
    with open('soup.html', 'r') as f:
        soup = BS(f, "html.parser")

    download_images(soup)

if __name__ == '__main__':
    main()
[/PYTHON]
[JAVA]
/**
 * Copyright (C), 2018-2019, XXX Inc. All rights reserved.
 *
 * This file is part of XXX.
 *
 * XXX can be distributed under the terms of the GNU General Public License Version 3
 * as published by the Free Software Foundation with the addition of the following
 * permission added to Section 15 as permitted in Section 7(a): FOR ANY PART OF THE
 * COVERED WORK IN WHICH THE COPYRIGHT IS OWNED BY XXX, XXX SHALL EXCEPT AS
 * SPECIFIED BELOW, ALL RIGHTS ARE RESERVED.
 *
 * The "GNU General Public License" is available at
 *    http://www.gnu.org/licenses/gpl-3.0.txt
 */
package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import org.w3c.dom.Text;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.d(TAG, "onCreate: ");
        TextView textView = findViewById(R.id.textView);
        textView.setText("Hello World!");
    }
}
[/JAVA]
