#coding: utf-8
require 'sinatra'
set :bind, '0.0.0.0'

get '/' do
  @titulo = "Robin Bird&trade; Machine Learning"
  haml :index
end

get '/download' do
  @titulo = "Robin Bird&trade; Machine Learning"
  haml :download
end

get '/quickstart' do
  @titulo = "Robin Bird&trade; Machine Learning"
  haml :quickstart
end

get '/documentation' do
  @titulo = "Robin Bird&trade; Machine Learning"
  haml :documentation
end

get '/training' do
  @titulo = "Robin Bird&trade; Machine Learning"
  haml :training
end

