[PYTHON]
import os
from datetime import datetime

from google.cloud import storage
from flask import session, request, current_app
from wtforms import StringField, PasswordField, BooleanField, SubmitField
from wtforms.validators import DataRequired, Email, EqualTo
from itsdangerous import URLSafeTimedSerializer, SignatureExpired

from config import Config
from models import User
from utils.gcp import upload_file_to_gcs
from utils.decorators import admin_required
from utils.email import send_reset_password_email
from .forms import ResetPasswordForm
from .utils import get_user_by_id, update_user


def reset_password(user_id):
    user = get_user_by_id(user_id)
    if not user:
        return {'error': 'User not found'}, 404

    # Generate password token
    serializer = URLSafeTimedSerializer(current_app.config['SECRET_KEY'])
    password_token = serializer.dumps(user.email)
    password_token = password_token.decode('utf-8')

    # Save password token to user object and update it in the database
    user.password_reset_token = password_token
    user.password_requested_at = datetime.utcnow()
    update_user(user)

    # Send reset password email
    send_reset_password_email(user.email, password_token)

    return {'message': 'Password reset email sent'}, 200


def reset_password_confirm(token):
    serializer = URLSafeTimedSerializer(current_app.config['SECRET_KEY'])

    try:
        email = serializer.loads(token, max_age=86400)
    except SignatureExpired:
        return {'error': 'Password reset token is invalid or has expired'}, 400

    user = get_user_by_id(User.email == email)
    if not user:
        return {'error': 'User not found'}, 404

    return {'message': 'Password successfully reset'}


def upload():
    storage_client = storage.Client()
    bucket = storage_client.get_bucket(Config.GCP_BUCKET)

    if request.method == 'POST':
        file = request.files['file']
        filename = f'{datetime.utcnow().timestamp()}{os.path.splitext(file.filename)[1]}'
        blob = bucket.blob(f'users/{session["user_id"]}/{filename}')
        blob.upload_from_string(file.read(), content_type=request.content_type)

        user = get_user_by_id(session['user_id'])
        user.profile_picture = filename
        update_user(user)

        return {'message': 'File uploaded successfully'}


@admin_required
def upload_to_gcs():
    storage_client = storage.Client()
    bucket = storage_client.get_bucket(Config.GCP_BUCKET)

    if request.method == 'POST':
        file = request.files['file']
        blob = bucket.blob(f'users/{session["user_id"]}/{file.filename}')
        blob.upload_from_string(file.read(), content_type=request.content_type)

        user = get_user_by_id(session['user_id'])
        user.profile_picture = file.filename
        update_user(user)

        return {'message': 'File uploaded successfully'}


def delete():
    storage_client = storage.Client()
    bucket = storage_client.get_bucket(Config.GCP_BUCKET)

    if request.method == 'POST':
        filename = request.form['filename']
        blob = bucket.blob(f'users/{session["user_id"]}/{filename}')
        blob.delete()

        user = get_user_by_id(session['user_id'])
        user.profile_picture = ''
        update_user(user)

        return {'message': 'File deleted successfully'}


def change_password():
    if request.method == 'POST':
        password = request.form['password']
        confirm_password = request.form['confirm_password']

        if not password or not confirm_password:
            return {'error': 'Please enter both fields'}, 400

        user = get_user_by_id(session['user_id'])
        user.set_password(password)
        update_user(user)

        return {'message': 'Password updated successfully'}


def reset_password_request():
    if request.method == 'POST':
        email = request.form['email']

        # Check if user exists
        user = get_user_by_id(User.email == email)
        if not user:
            return {'error': 'User not found'}, 404

        # Generate password token
        serializer = URLSafeTimedSerializer(current_app.config['SECRET_KEY'])
        password_token = serializer.dumps(user.email)
        password_token = password_token.decode('utf-8')

        # Save password token to user object and update it in the database
        user.password_reset_token = password_token
        user.password_requested_at = datetime.utcnow()
        update_user(user)

        # Send reset password email
        send_reset_password_email(user.email, password_token)

        return {'message': 'Password reset email sent'}, 200


def reset_password_confirm():
    if request.method == 'POST':
        token = request.form['token']
        new_password = request.form['new_password']
        confirm_password = request.form['confirm_password']

        # Check if both passwords match
        if not new_password or not confirm_password:
            return {'error': 'Please enter both fields'}, 400

        serializer = URLSafeTimedSerializer(current_app.config['SECRET_KEY'])

        try:
            email = serializer.loads(token, max_age=86400)
        except SignatureExpired:
            return {'error': 'Password reset token is invalid or has expired'}, 400

        user = get_user_by_id(User.email == email)
        if not user:
            return {'error': 'User not found'}, 404

        # Update password
        user.set_password(new_password)
        update_user(user)

        return {'message': 'Password successfully reset'}


def get_profile():
    user = get_user_by_id(session['user_id'])
    if not user:
        return {'error': 'User not found'}, 404

    profile = {
        'email': user.email,
        'username': user.username,
        'first_name': user.first_name,
        'last_name': user.last_name,
        'profile_picture': user.profile_picture,
    }

    return profile
[/PYTHON]
[TYPESCRIPT]
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';
import { User, Profile } from './models';

@Injectable({ providedIn: 'root' })
export class AuthService {
  constructor(private http: HttpClient) {}

  signup(email: string, password: string): Observable<User> {
    return this.http.post<User>(`/api/auth/signup`, { email, password });
  }

  login(email: string, password: string): Observable<{ accessToken: string }> {
    return this.http.post<{ accessToken: string }>(`/api/auth/login`, { email, password });
  }

  logout(): void {
    // remove user from local storage to log user out
    localStorage.removeItem('user');
  }

  getLoggedUser(): User | null {
    const user = JSON.parse(localStorage.getItem('user'));
    return user;
  }
}

export interface Profile {
  id: number,
  username: string,
  email: string,
  firstName: string,
  lastName: string,
  profilePicture?: any
}

export interface User extends Profile {
  password: string;
}
[/TYPESCRIPT]
