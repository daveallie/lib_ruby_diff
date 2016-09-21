require 'spec_helper'

describe LibRubyDiff do
  it 'has a version number' do
    expect(LibRubyDiff::VERSION).not_to be nil
  end

  it 'generates the correct signature' do
    Dir.mktmpdir do |dir|
      sig_file = File.join(dir, 'sig_output.sig')
      base = 'spec/bases/sig_base.in'

      LibRubyDiff.signature(base, sig_file)

      expected_sig = File.expand_path('spec/sigs/sig_base.sig')
      expect(File.read(sig_file)).to eq(File.read(expected_sig))
    end
  end

  it 'applies deltas correctly' do
    Dir.mktmpdir do |dir|
      empty = File.join(dir, 'empty.in')
      File.write(empty, 'w'){|f|}
      files = Dir['spec/deltas/*.delta']
      expect(files.length).to be > 0

      files.each do |file|
        input_name = file.split('/').last.split('.').first
        actual_output = File.join(dir, "#{input_name}.output")

        LibRubyDiff.patch(empty, file, actual_output)

        expected_output = "spec/deltas/#{input_name}.expect"
        expect(File.read(actual_output)).to eq(File.read(expected_output))
      end
    end
  end

  it 'does all three actions correctly' do
    Dir.mktmpdir do |dir|
      base_file = 'spec/bases/base.in'
      files = Dir['spec/new_files/*.in']
      expect(files.length).to be > 0

      files.each do |file|
        file_name = file.split('/').last.split('.').first
        sig_file = File.join(dir, "#{file_name}.sig")
        delta_file = File.join(dir, "#{file_name}.delta")
        result_file = File.join(dir, "#{file_name}.output")

        LibRubyDiff.signature(base_file, sig_file)
        LibRubyDiff.delta(file, sig_file, delta_file)
        LibRubyDiff.patch(base_file, delta_file, result_file)

        expect(File.read(result_file)).to eq(File.read(file))
      end
    end
  end
end
