class ApplicationController < ActionController::Base
  include Console::Rescue

  # Adding the following line to skip CSRF protection for specific actions or entire controllers where it's not necessary.
  skip_before_action :verify_authenticity_token, only: [:non_critical_action]
end
