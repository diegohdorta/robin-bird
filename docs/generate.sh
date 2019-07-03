#!/usr/bin/env sh
bundle exec rake build
evince pdf/robinbird.pdf
