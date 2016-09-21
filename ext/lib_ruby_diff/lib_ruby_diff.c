#include <ruby.h>
#include <stdio.h>
#include <stdlib.h>
#include <librsync.h>

VALUE LibRubyDiff = Qnil;

static VALUE lib_ruby_diff_signature(VALUE self, VALUE base_file_path, VALUE signature_file_path) {
  FILE *base_file, *signature_file;
  rs_result result;
  rs_stats_t stats;

  base_file = fopen(StringValuePtr(base_file_path), "rb");
  signature_file = fopen(StringValuePtr(signature_file_path), "wb");

  if (!base_file || !signature_file) {
    rb_raise(rb_eIOError, "Failed to open required files. Check they exist and you have the correct permissions.");
    return Qnil;
  }

  result = rs_sig_file(base_file, signature_file, RS_DEFAULT_BLOCK_LEN, 0, RS_BLAKE2_SIG_MAGIC, &stats);
  if (result != RS_DONE) {
    rb_raise(rb_eStandardError, "Failed to create signature file.");
    return Qnil;
  }

  fclose(base_file);
  fclose(signature_file);

  return Qnil;
}

static VALUE lib_ruby_diff_delta(VALUE self, VALUE new_file_path, VALUE signature_file_path, VALUE delta_file_path) {
  FILE *new_file, *signature_file, *delta_file;
  rs_result result;
  rs_stats_t stats;
  rs_signature_t *signature;

  new_file = fopen(StringValuePtr(new_file_path), "rb");
  signature_file = fopen(StringValuePtr(signature_file_path), "rb");
  delta_file = fopen(StringValuePtr(delta_file_path), "wb");

  if (!new_file || !signature_file || !delta_file) {
    rb_raise(rb_eIOError, "Failed to open required files. Check they exist and you have the correct permissions.");
    return Qnil;
  }

  result = rs_loadsig_file(signature_file, &signature, &stats);
  if (result != RS_DONE) {
    rb_raise(rb_eStandardError, "Failed to load signature file.");
    return Qnil;
  }

  result = rs_build_hash_table(signature);
  if (result != RS_DONE) {
    rb_raise(rb_eStandardError, "Failed to build hash table.");
    return Qnil;
  }

  result = rs_delta_file(signature, new_file, delta_file, &stats);
  if (result != RS_DONE) {
    rb_raise(rb_eStandardError, "Failed to create delta file.");
    return Qnil;
  }

  rs_free_sumset(signature);

  fclose(new_file);
  fclose(signature_file);
  fclose(delta_file);

  return Qnil;
}

static VALUE lib_ruby_diff_patch(VALUE self, VALUE base_file_path, VALUE delta_file_path, VALUE patched_file_path) {
    FILE *base_file, *delta_file, *patched_file;
    rs_stats_t stats;
    rs_result result;

    base_file = fopen(StringValuePtr(base_file_path), "rb");
    delta_file = fopen(StringValuePtr(delta_file_path), "rb");
    patched_file = fopen(StringValuePtr(patched_file_path), "wb");

    if (!base_file || !delta_file || !patched_file) {
      rb_raise(rb_eIOError, "Failed to open required files. Check they exist and you have the correct permissions.");
      return Qnil;
    }

    result = rs_patch_file(base_file, delta_file, patched_file, &stats);
    if (result != RS_DONE) {
      rb_raise(rb_eStandardError, "Failed to create patched file.");
      return Qnil;
    }

    fclose(base_file);
    fclose(delta_file);
    fclose(patched_file);

    return Qnil;
}

void Init_lib_ruby_diff() {
  LibRubyDiff = rb_define_module("LibRubyDiff");
  rb_define_singleton_method(LibRubyDiff, "signature", lib_ruby_diff_signature, 2);
  rb_define_singleton_method(LibRubyDiff, "delta", lib_ruby_diff_delta, 3);
  rb_define_singleton_method(LibRubyDiff, "patch", lib_ruby_diff_patch, 3);
}
