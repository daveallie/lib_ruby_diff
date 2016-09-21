require "bundler/gem_tasks"
require "rspec/core/rake_task"
require "rake/extensiontask"

Rake::ExtensionTask.new "lib_ruby_diff" do |ext|
  ext.lib_dir = "lib/lib_ruby_diff"
end

RSpec::Core::RakeTask.new(:spec)

task :default => :spec
