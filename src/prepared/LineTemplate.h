// generated by kiste2cpp
#pragma once
#include <kiste/terminal.h>

/*
 * Copyright (c) 2015-2015, Roland Bock
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "line_type.h"
#include "segment_type.h"

namespace kiste
{
  template <typename DERIVED_T, typename DATA_T, typename SERIALIZER_T>
  struct LineTemplate_t
  {
    DERIVED_T& child;
    using _data_t = DATA_T;
    const _data_t& data;
    using _serializer_t = SERIALIZER_T;
    _serializer_t& _serialize;

    LineTemplate_t(DERIVED_T& derived, const DATA_T& data_, SERIALIZER_T& serialize)
        : child(derived), data(data_), _serialize(serialize)
    {
    }

    void open_exception_handling()
    {
      if (data._report_exceptions)
      {
        _serialize.text(" try"
                        " { ");
      }
    }

    void close_exception_handling(const std::string& expression)
    {
      if (data._report_exceptions)
      {
        _serialize.text(" }"
                        " catch(...)"
                        " {"
                        " _serialize.report_exception(__LINE__, \"");
        _serialize.escape(expression);
        _serialize.text("\", std::current_exception());"
                        " } ");
      }
    }

    void escape(const std::string& expression)
    {
      static_assert(std::is_same<decltype(open_exception_handling()), void>::value,
                    "$call{} requires void expression");
      (open_exception_handling());
      _serialize.text("_serialize.escape(");
      _serialize.raw(expression);
      _serialize.text(");");
      static_assert(std::is_same<decltype(close_exception_handling(expression)), void>::value,
                    "$call{} requires void expression");
      (close_exception_handling(expression));
    }

    void raw(const std::string& expression)
    {
      static_assert(std::is_same<decltype(open_exception_handling()), void>::value,
                    "$call{} requires void expression");
      (open_exception_handling());
      _serialize.text("_serialize.raw(");
      _serialize.raw(expression);
      _serialize.text(");");
      static_assert(std::is_same<decltype(close_exception_handling(expression)), void>::value,
                    "$call{} requires void expression");
      (close_exception_handling(expression));
    }

    void call(const std::string& expression)
    {
      static_assert(std::is_same<decltype(open_exception_handling()), void>::value,
                    "$call{} requires void expression");
      (open_exception_handling());
      _serialize.text("static_assert(std::is_same<decltype(");
      _serialize.raw(expression);
      _serialize.text("), void>::value, \"$call{} requires void expression\"); (");
      _serialize.raw(expression);
      _serialize.text(");");
      static_assert(std::is_same<decltype(close_exception_handling(expression)), void>::value,
                    "$call{} requires void expression");
      (close_exception_handling(expression));
    }

    void open_string(bool& string_opened)
    {
      if (not string_opened)
      {
        _serialize.text("_serialize.text(");
      }
      string_opened = true;
    }

    void close_string(bool& string_opened)
    {
      if (string_opened)
      {
        _serialize.text(");");
      }
      string_opened = false;
    }

    void text_segment(const std::string& line)
    {
      _serialize.text("\"");
      _serialize.escape(line);
      _serialize.text("\"");
    }

    void render_none()
    {
      _serialize.text("\n");
    }

    template <typename Line>
    void render_text(const Line& line)
    {
      for (std::size_t i = 0; i < line._curly_level; ++i)
      {
        _serialize.text("  ");
      }
      auto string_opened = line.starts_with_text() && line._previous_line_ends_with_text;
      if (string_opened)
      {
        _serialize.text("                ");
      }
      for (const auto& segment : line._segments)
      {
        switch (segment._type)
        {
        case segment_type::cpp:
          break;
        case segment_type::text:
          static_assert(std::is_same<decltype(open_string(string_opened)), void>::value,
                        "$call{} requires void expression");
          (open_string(string_opened));
          static_assert(std::is_same<decltype(text_segment(segment._text)), void>::value,
                        "$call{} requires void expression");
          (text_segment(segment._text));
          break;
        case segment_type::trim_trailing_return:
          break;
        case segment_type::escape:
          static_assert(std::is_same<decltype(close_string(string_opened)), void>::value,
                        "$call{} requires void expression");
          (close_string(string_opened));
          static_assert(std::is_same<decltype(escape(segment._text)), void>::value,
                        "$call{} requires void expression");
          (escape(segment._text));
          break;
        case segment_type::call:
          static_assert(std::is_same<decltype(close_string(string_opened)), void>::value,
                        "$call{} requires void expression");
          (close_string(string_opened));
          static_assert(std::is_same<decltype(call(segment._text)), void>::value,
                        "$call{} requires void expression");
          (call(segment._text));
          break;
        case segment_type::raw:
          static_assert(std::is_same<decltype(close_string(string_opened)), void>::value,
                        "$call{} requires void expression");
          (close_string(string_opened));
          static_assert(std::is_same<decltype(raw(segment._text)), void>::value,
                        "$call{} requires void expression");
          (raw(segment._text));
          break;
        }
      }
      if (not line._next_line_starts_with_text)
      {
        static_assert(std::is_same<decltype(close_string(string_opened)), void>::value,
                      "$call{} requires void expression");
        (close_string(string_opened));
      }
      _serialize.text("\n");
    }

    template <typename Line>
    void render_cpp(const Line& line)
    {
      _serialize.raw(line._segments[0]._text);
      _serialize.text("\n");
    }
  };

  template <typename DATA_T, typename SERIALIZER_T>
  auto LineTemplate(const DATA_T& data, SERIALIZER_T& serialize)
      -> LineTemplate_t<kiste::terminal_t, DATA_T, SERIALIZER_T>
  {
    return {kiste::terminal, data, serialize};
  }
}
