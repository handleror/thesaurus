#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ruby.h"

VALUE rb_mThesaurus;

static const char *dict;
size_t len;

void
raiseError(const char *msg) {
  rb_raise(rb_eRuntimeError, "%s", msg);
}


const char *
opendict(const char *filename, void (*err)(const char *)) {
  struct stat sb;

  int fd = open(filename, O_RDONLY);
  if (fd < 0) {
    err("Cannot open dictionary file");
    return 0;
  }
  fstat(fd, &sb);
  len = sb.st_size;

  const char *dict = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (dict == MAP_FAILED) {
    err("Cannot mmap dictionary file");
    return 0;
  }

  close(fd);

  return dict;
}



void
search(const char *query, const char *dictfile, void (*callback)(const char *, size_t)) {
  if (!dict) {
    dict = opendict(dictfile, raiseError);
    if (!dict) {
      return;
    }
  }

  const char *p = dict;
  while (p < dict + len) {
    const char *line = p;
    int endofline = 0;

    while (p < dict + len && !endofline) {
      const char *q = query;

      /* match as much of the query as possible */
      while (*p && *q && *p == *q) {
        p++;
        q++;
      }

      /* Matched if we're at the end of the search term AND
       * at the end of a word in the dictionary
       */
      if (*q == 0 && (*p == ',' || *p == '\n')) {
        while (*p != '\n') {
          p++;
        }
        callback(line, p - line);
        continue;
      }

      /* Not a full match - skip to next word */
      while (*p != ',' && *p != '\n') {
        p++;
      }

      if (*p == '\n') {
        endofline = 1;
      }

      p++;
    }
  }

  return;
}

void
yieldValue(const char *line, size_t len) {
  rb_yield(rb_str_new(line, len));
}

VALUE
lookup(VALUE self, VALUE pattern) {
  const char *pat = StringValueCStr(pattern);
  VALUE dict = rb_iv_get(self, "@dict");
  const char *dictFile = StringValueCStr(dict);
  search(pat, dictFile, yieldValue);
  return Qnil;
}

void
Init_thesaurus(void)
{
  rb_mThesaurus = rb_define_module("Thesaurus");
  rb_define_singleton_method(rb_mThesaurus, "_lookup", lookup, 1);
}
