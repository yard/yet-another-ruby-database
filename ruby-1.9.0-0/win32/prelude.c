#include "ruby/ruby.h"
#include "vm_core.h"

static const char prelude_name0[] = "prelude.rb";
static const char prelude_code0[] =
"\n"
"# Mutex\n"
"\n"
"class Mutex\n"
"  def synchronize\n"
"    self.lock\n"
"    begin\n"
"      yield\n"
"    ensure\n"
"      self.unlock\n"
"    end\n"
"  end\n"
"end\n"
"\n"
"# Thread\n"
"\n"
"class Thread\n"
"  MUTEX_FOR_THREAD_EXCLUSIVE = Mutex.new\n"
"  def self.exclusive\n"
"    MUTEX_FOR_THREAD_EXCLUSIVE.synchronize{\n"
"      yield\n"
"    }\n"
"  end\n"
"end\n"
"\n"
;
static const char prelude_name1[] = "gem_prelude.rb";
static const char prelude_code1[] =
"TMP_RUBY_PREFIX = $:.reverse.find{|e|e!=\".\"}.sub(%r{(.*)/lib/.*}m, \"\\\\1\")\n"
"# empty gem_prelude.rb\n"
"#\n"
"# p Gem::Enable\n"
"\n"
"if defined?(Gem::Enable) && Gem::Enable\n"
"#t = Time.now\n"
"  \n"
"module Kernel\n"
"\n"
"  def gem(gem_name, *version_requirements)\n"
"    Gem.push_gem_version_on_load_path(gem_name, *version_requirements)\n"
"  end\n"
"\n"
"end\n"
"\n"
"module Gem\n"
"  \n"
"  ConfigMap = {\n"
"    :sitedir => \"#{TMP_RUBY_PREFIX}/lib/ruby/site_ruby\",\n"
"    :ruby_version => \"1.9.0\",\n"
"    :libdir => \"#{TMP_RUBY_PREFIX}/lib\",\n"
"    :sitelibdir => \"#{TMP_RUBY_PREFIX}/lib/ruby/site_ruby/1.9.0\",\n"
"    :arch => \"i386-mswin32\",\n"
"    :bindir => \"#{TMP_RUBY_PREFIX}/bin\",\n"
"    :EXEEXT => \".exe\",\n"
"    :RUBY_SO_NAME => \"msvcrt-ruby190\",\n"
"    :ruby_install_name => \"ruby\"\n"
"  }\n"
"\n"
"  class << self\n"
"\n"
"    def default_dir\n"
"      if defined? RUBY_FRAMEWORK_VERSION\n"
"        return File.join(File.dirname(ConfigMap[:sitedir]), \"Gems\")\n"
"      else\n"
"        File.join(ConfigMap[:libdir], 'ruby', 'gems', ConfigMap[:ruby_version])\n"
"      end\n"
"    end\n"
"\n"
"    def dir\n"
"      @gem_home ||= nil\n"
"      set_home(ENV['GEM_HOME'] || default_dir) unless @gem_home\n"
"      @gem_home\n"
"    end\n"
"\n"
"    def path\n"
"      @gem_path ||= nil\n"
"      unless @gem_path\n"
"        paths = [ENV['GEM_PATH']]\n"
"        paths << APPLE_GEM_HOME if defined? APPLE_GEM_HOME\n"
"        set_paths(paths.compact.join(File::PATH_SEPARATOR))\n"
"      end\n"
"      @gem_path\n"
"    end\n"
"\n"
"    # Set the Gem home directory (as reported by +dir+).\n"
"    def set_home(home)\n"
"      @gem_home = home\n"
"      ensure_gem_subdirectories(@gem_home)\n"
"    end\n"
"\n"
"    def set_paths(gpaths)\n"
"      if gpaths\n"
"        @gem_path = gpaths.split(File::PATH_SEPARATOR)\n"
"        @gem_path << Gem.dir\n"
"      else\n"
"        @gem_path = [Gem.dir]\n"
"      end\n"
"      @gem_path.uniq!\n"
"      @gem_path.each do |gp| ensure_gem_subdirectories(gp) end\n"
"    end\n"
"    \n"
"    def ensure_gem_subdirectories(path)\n"
"    end\n"
"\n"
"  end\n"
"\n"
"  module QuickLoader\n"
"\n"
"    class << self\n"
"      def load_full_rubygems_library\n"
"        class << Gem\n"
"          Gem.methods(false).each do |method_name|\n"
"            undef_method method_name\n"
"          end\n"
"        end\n"
"\n"
"        Kernel.send :undef_method, :gem\n"
"\n"
"        $\".delete File.join(Gem::ConfigMap[:libdir], 'ruby',\n"
"                            Gem::ConfigMap[:ruby_version], 'rubygems.rb')\n"
"\n"
"        require 'rubygems'\n"
"      end\n"
"    end\n"
"\n"
"    GemPaths = {}\n"
"    GemVersions = {}\n"
"    \n"
"    def push_gem_version_on_load_path(gem_name, *version_requirements)\n"
"      if version_requirements.empty?\n"
"        unless GemPaths.has_key?(gem_name)\n"
"          raise LoadError.new(\"Could not find RubyGem #{gem_name} (>= 0)\\n\") \n"
"        end\n"
"        # highest version gems already active\n"
"        return false\n"
"      else\n"
"        if version_requirements.length > 1\n"
"          QuickLoader.load_full_rubygems_library\n"
"          return gem(gem_name, *version_requirements)\n"
"        end\n"
"        requirement, version = version_requirements[0].split\n"
"        requirement.strip!\n"
"        if requirement == \">\" || requirement == \">=\"\n"
"          if (GemVersions[gem_name] <=> Gem.calculate_integers_for_gem_version(version)) >= 0\n"
"            return false \n"
"          end\n"
"        elsif requirement == \"~>\"\n"
"          loaded_version = GemVersions[gem_name]\n"
"          required_version = Gem.calculate_integers_for_gem_version(version)\n"
"          if loaded_version && (loaded_version[0] == required_version[0])\n"
"            return false\n"
"          end\n"
"        end\n"
"        QuickLoader.load_full_rubygems_library\n"
"        gem(gem_name, *version_requirements)\n"
"      end\n"
"    end\n"
"\n"
"    def calculate_integers_for_gem_version(gem_version)\n"
"      numbers = gem_version.split(\".\").collect {|n| n.to_i}\n"
"      numbers.pop while numbers.last == 0\n"
"      numbers << 0 if numbers.empty?\n"
"      numbers\n"
"    end\n"
"  \n"
"    def push_all_highest_version_gems_on_load_path\n"
"      Gem.path.each do |path|\n"
"        gems_directory = File.join(path, \"gems\")\n"
"        if File.exist?(gems_directory)\n"
"          Dir.entries(gems_directory).each do |gem_directory_name|\n"
"            next if gem_directory_name == \".\" || gem_directory_name == \"..\"\n"
"            dash = gem_directory_name.rindex(\"-\")\n"
"            next if dash.nil?\n"
"            gem_name = gem_directory_name[0...dash]\n"
"            current_version = GemVersions[gem_name]\n"
"            new_version = calculate_integers_for_gem_version(gem_directory_name[dash+1..-1])\n"
"            if current_version\n"
"              if (current_version <=> new_version) == -1\n"
"                GemVersions[gem_name] = new_version\n"
"                GemPaths[gem_name] = File.join(gems_directory, gem_directory_name)\n"
"              end\n"
"            else\n"
"              GemVersions[gem_name] = new_version\n"
"              GemPaths[gem_name] = File.join(gems_directory, gem_directory_name)\n"
"            end\n"
"          end\n"
"        end\n"
"      end\n"
"      require_paths = []\n"
"      GemPaths.values.each do |path|\n"
"        if File.exist?(File.join(path, \".require_paths\"))\n"
"          require_paths.concat(File.read(File.join(path, \".require_paths\")).split.map {|require_path| File.join(path, require_path)})\n"
"        else\n"
"          require_paths << File.join(path, \"bin\") if File.exist?(File.join(path, \"bin\"))\n"
"          require_paths << File.join(path, \"lib\") if File.exist?(File.join(path, \"lib\"))\n"
"        end\n"
"      end\n"
"\n"
"      # gem directories must come after -I and ENV['RUBYLIB']\n"
"      $:[$:.index(ConfigMap[:sitelibdir]),0] = require_paths\n"
"    end\n"
"\n"
"    def const_missing(constant)\n"
"      QuickLoader.load_full_rubygems_library\n"
"      Gem.const_get(constant)\n"
"    end\n"
"\n"
"    def method_missing(method, *args, &block)\n"
"      QuickLoader.load_full_rubygems_library\n"
"      super unless Gem.respond_to?(method)\n"
"      Gem.send(method, *args, &block)\n"
"    end\n"
"  end\n"
"  \n"
"  extend QuickLoader\n"
"\n"
"end\n"
"\n"
"begin\n"
"  Gem.push_all_highest_version_gems_on_load_path\n"
"  $\" << File.join(Gem::ConfigMap[:libdir], \"ruby\",\n"
"                  Gem::ConfigMap[:ruby_version], \"rubygems.rb\")\n"
"rescue Exception => e\n"
"  puts \"Error loading gem paths on load path in gem_prelude\"\n"
"  puts e\n"
"  puts e.backtrace.join(\"\\n\")\n"
"end\n"
"\n"
"#puts \"Gem load in #{Time.now - t} seconds\"\n"
"end # Gem::Enable\n"
"Object.class_eval { remove_const \"TMP_RUBY_PREFIX\" }"
;

void
Init_prelude(void)
{
  rb_iseq_eval(rb_iseq_compile(
    rb_str_new(prelude_code0, sizeof(prelude_code0) - 1),
    rb_str_new(prelude_name0, sizeof(prelude_name0) - 1),
    INT2FIX(1)));

  rb_iseq_eval(rb_iseq_compile(
    rb_str_new(prelude_code1, sizeof(prelude_code1) - 1),
    rb_str_new(prelude_name1, sizeof(prelude_name1) - 1),
    INT2FIX(0)));

#if 0
    puts(prelude_code0);
    puts(prelude_code1);
#endif
}