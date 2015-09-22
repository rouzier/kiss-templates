#pragma once
#include <kiste/terminal.h>

#line 1 "../src/ClassTemplate.kiste"
namespace kiste
{
  template <typename DERIVED_T, typename DATA_T, typename SERIALIZER_T>
  struct ClassTemplate_t
  {
    DERIVED_T& child;
    using _data_t = DATA_T;
    const _data_t& data;
    using _serializer_t = SERIALIZER_T;
    _serializer_t& _serialize;

    ClassTemplate_t(DERIVED_T& derived, const DATA_T& data_, SERIALIZER_T& serialize)
        : child(derived), data(data_), _serialize(serialize)
    {
    }
// ----------------------------------------------------------------------
#line 4

    void render_header()
    {
      _serialize.text("template<typename DERIVED_T, typename DATA_T, typename SERIALIZER_T>\n"
                      "struct ");
      _serialize.escape(data.class_name);
      _serialize.text("_t\n");
      if (!data.parent_class_name.empty())
      {
        _serialize.text("   : public ");
        _serialize.escape(data.parent_class_name);
        _serialize.text("_t<");
        _serialize.escape(data.class_name);
        _serialize.text("_t<DERIVED_T, DATA_T, SERIALIZER_T>, DATA_T, SERIALIZER_T>\n");
      }
      _serialize.text("{\n");
      if (!data.parent_class_name.empty())
      {
        _serialize.text("  using _parent_t = ");
        _serialize.escape(data.parent_class_name);
        _serialize.text("_t<");
        _serialize.escape(data.class_name);
        _serialize.text("_t, DATA_T, SERIALIZER_T>;\n"
                        "  _parent_t& parent;\n");
      }
      _serialize.text("  DERIVED_T& child;\n"
                      "  using _data_t = DATA_T;\n"
                      "  const _data_t& data;\n"
                      "  using _serializer_t = SERIALIZER_T;\n"
                      "  _serializer_t& _serialize;\n"
                      "\n"
                      "  ");
      _serialize.escape(data.class_name);
      _serialize.text("_t(DERIVED_T& derived, const DATA_T& data_, SERIALIZER_T& serialize):\n");
      if (!data.parent_class_name.empty())
      {
        _serialize.text("  _parent_t{*this, data_, serialize},\n"
                        "  parent{*this},\n");
      }
      _serialize.text(
          "    child(derived),\n"
          "    data(data_),\n"
          "    _serialize(serialize)\n"
          "  {}\n"
          "  // ----------------------------------------------------------------------\n"
          "#line ");
      _serialize.escape(data.line_no + 1);
      _serialize.text("\n");
    }

    void render_footer()
    {
      _serialize.text(
          "  // ----------------------------------------------------------------------\n"
          "#line ");
      _serialize.escape(data.line_no);
      _serialize.text("\n"
                      "};\n"
                      "\n"
                      "#line ");
      _serialize.escape(data.line_no);
      _serialize.text("\n"
                      "template<typename DATA_T, typename SERIALIZER_T>\n"
                      "auto ");
      _serialize.escape(data.class_name);
      _serialize.text("(const DATA_T& data, SERIALIZER_T& serialize)\n"
                      "  -> ");
      _serialize.escape(data.class_name);
      _serialize.text("_t<kiste::terminal_t, DATA_T, SERIALIZER_T>\n"
                      "{\n"
                      "  return {kiste::terminal, data, serialize};\n"
                      "}\n"
                      "\n"
                      "#line ");
      _serialize.escape(data.line_no + 1);
      _serialize.text("\n");
    }

// ----------------------------------------------------------------------
#line 56
  };

#line 56
  template <typename DATA_T, typename SERIALIZER_T>
  auto ClassTemplate(const DATA_T& data, SERIALIZER_T& serialize)
      -> ClassTemplate_t<kiste::terminal_t, DATA_T, SERIALIZER_T>
  {
    return {kiste::terminal, data, serialize};
  }

#line 57
}