class ApplicationController < ActionController::Base
  include Console::Rescue

  # Corrected version of the code with CSRF protection enabled
  protect_from_forgery with: :exception
end
