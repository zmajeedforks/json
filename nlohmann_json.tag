<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="struct">
    <name>nlohmann::adl_serializer</name>
    <filename>structnlohmann_1_1adl__serializer.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static auto</type>
      <name>from_json</name>
      <anchorfile>structnlohmann_1_1adl__serializer_a2c544585b8b1828a0f1eecd831d0496e.html</anchorfile>
      <anchor>a2c544585b8b1828a0f1eecd831d0496e</anchor>
      <clangid>c:@N@nlohmann@ST&gt;2#T#T@adl_serializer@FT@&gt;2#T#Tfrom_json#&amp;&amp;t1.0#&amp;t1.1#I#S</clangid>
      <arglist>(BasicJsonType &amp;&amp;j, ValueType &amp;val) noexcept(noexcept(::nlohmann::from_json(std::forward&lt; BasicJsonType &gt;(j), val))) -&gt; decltype(::nlohmann::from_json(std::forward&lt; BasicJsonType &gt;(j), val), void())</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static auto</type>
      <name>to_json</name>
      <anchorfile>structnlohmann_1_1adl__serializer_a01b867bd5dce5249d4f7433b8f27def6.html</anchorfile>
      <anchor>a01b867bd5dce5249d4f7433b8f27def6</anchor>
      <clangid>c:@N@nlohmann@ST&gt;2#T#T@adl_serializer@FT@&gt;2#T#Tto_json#&amp;t1.0#&amp;&amp;t1.1#I#S</clangid>
      <arglist>(BasicJsonType &amp;j, ValueType &amp;&amp;val) noexcept(noexcept(::nlohmann::to_json(j, std::forward&lt; ValueType &gt;(val)))) -&gt; decltype(::nlohmann::to_json(j, std::forward&lt; ValueType &gt;(val)), void())</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>nlohmann::basic_json</name>
    <filename>classnlohmann_1_1basic__json.html</filename>
    <templarg>ObjectType</templarg>
    <templarg>ArrayType</templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg>AllocatorType</templarg>
    <templarg>JSONSerializer</templarg>
    <member kind="typedef">
      <type>detail::error_handler_t</type>
      <name>error_handler_t</name>
      <anchorfile>classnlohmann_1_1basic__json_ae56b6bfbb1f6d2f43611f2ada4f9e5f2.html</anchorfile>
      <anchor>ae56b6bfbb1f6d2f43611f2ada4f9e5f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::initializer_list&lt; detail::json_ref&lt; basic_json &gt; &gt;</type>
      <name>initializer_list_t</name>
      <anchorfile>classnlohmann_1_1basic__json_ad70a098fbc01c53497db29d3b5b656a9.html</anchorfile>
      <anchor>ad70a098fbc01c53497db29d3b5b656a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>detail::input_format_t</type>
      <name>input_format_t</name>
      <anchorfile>classnlohmann_1_1basic__json_a2ddbac818a4c84a7377b1bbd25363588.html</anchorfile>
      <anchor>a2ddbac818a4c84a7377b1bbd25363588</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>::nlohmann::json_pointer&lt; basic_json &gt;</type>
      <name>json_pointer</name>
      <anchorfile>classnlohmann_1_1basic__json_a6886a5001f5b449ad316101a311ce536.html</anchorfile>
      <anchor>a6886a5001f5b449ad316101a311ce536</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>json_sax&lt; basic_json &gt;</type>
      <name>json_sax_t</name>
      <anchorfile>classnlohmann_1_1basic__json_aa865c3eb68b6ebdd647173774d2b5cdb.html</anchorfile>
      <anchor>aa865c3eb68b6ebdd647173774d2b5cdb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>JSONSerializer&lt; T, SFINAE &gt;</type>
      <name>json_serializer</name>
      <anchorfile>classnlohmann_1_1basic__json_a7768841baaaa7a21098a401c932efaff.html</anchorfile>
      <anchor>a7768841baaaa7a21098a401c932efaff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename parser::parse_event_t</type>
      <name>parse_event_t</name>
      <anchorfile>classnlohmann_1_1basic__json_aaceba2e4cf75fc983bb75c78c8742e65.html</anchorfile>
      <anchor>aaceba2e4cf75fc983bb75c78c8742e65</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename parser::parser_callback_t</type>
      <name>parser_callback_t</name>
      <anchorfile>classnlohmann_1_1basic__json_ab4f78c5f9fd25172eeec84482e03f5b7.html</anchorfile>
      <anchor>ab4f78c5f9fd25172eeec84482e03f5b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>detail::value_t</type>
      <name>value_t</name>
      <anchorfile>classnlohmann_1_1basic__json_ae8cbef097f7da18a781fc86587de6b90.html</anchorfile>
      <anchor>ae8cbef097f7da18a781fc86587de6b90</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>JSON_HEDLEY_RETURNS_NON_NULL const char *</type>
      <name>type_name</name>
      <anchorfile>classnlohmann_1_1basic__json_a9d75f6b5393b23a683d69605f9fb1f55.html</anchorfile>
      <anchor>a9d75f6b5393b23a683d69605f9fb1f55</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static allocator_type</type>
      <name>get_allocator</name>
      <anchorfile>classnlohmann_1_1basic__json_af4ac14224fbdd29d3547fcb11bb55c8f.html</anchorfile>
      <anchor>af4ac14224fbdd29d3547fcb11bb55c8f</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json@F@get_allocator#S</clangid>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>meta</name>
      <anchorfile>classnlohmann_1_1basic__json_a677318a34ade7f8177a2784c06aa3671.html</anchorfile>
      <anchor>a677318a34ade7f8177a2784c06aa3671</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json@F@meta#S</clangid>
      <arglist>()</arglist>
    </member>
    <member kind="friend">
      <type>friend struct</type>
      <name>detail::external_constructor</name>
      <anchorfile>classnlohmann_1_1basic__json_a6275ed57bae6866cdf5db5370a7ad47c.html</anchorfile>
      <anchor>a6275ed57bae6866cdf5db5370a7ad47c</anchor>
      <clangid>c:@N@nlohmann@N@detail@ST&gt;1#N$@N@nlohmann@N@detail@E@value_t@external_constructor</clangid>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>detail::exception</type>
      <name>exception</name>
      <anchorfile>classnlohmann_1_1basic__json_a9a0aced019cb1d65bb49703406c84970.html</anchorfile>
      <anchor>a9a0aced019cb1d65bb49703406c84970</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>detail::parse_error</type>
      <name>parse_error</name>
      <anchorfile>classnlohmann_1_1basic__json_af1efc2468e6022be6e35fc2944cabe4d.html</anchorfile>
      <anchor>af1efc2468e6022be6e35fc2944cabe4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>detail::invalid_iterator</type>
      <name>invalid_iterator</name>
      <anchorfile>classnlohmann_1_1basic__json_ac13d32f7cbd02d616e71d8dc30dadcbf.html</anchorfile>
      <anchor>ac13d32f7cbd02d616e71d8dc30dadcbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>detail::type_error</type>
      <name>type_error</name>
      <anchorfile>classnlohmann_1_1basic__json_a4010e8e268fefd86da773c10318f2902.html</anchorfile>
      <anchor>a4010e8e268fefd86da773c10318f2902</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>detail::out_of_range</type>
      <name>out_of_range</name>
      <anchorfile>classnlohmann_1_1basic__json_a28f7c2f087274a0012eb7a2333ee1580.html</anchorfile>
      <anchor>a28f7c2f087274a0012eb7a2333ee1580</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>detail::other_error</type>
      <name>other_error</name>
      <anchorfile>classnlohmann_1_1basic__json_a3333a5a8714912adda33a35b369f7b3d.html</anchorfile>
      <anchor>a3333a5a8714912adda33a35b369f7b3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>basic_json</type>
      <name>value_type</name>
      <anchorfile>classnlohmann_1_1basic__json_a2b3297873b70c080837e8eedc4fec32f.html</anchorfile>
      <anchor>a2b3297873b70c080837e8eedc4fec32f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>value_type &amp;</type>
      <name>reference</name>
      <anchorfile>classnlohmann_1_1basic__json_ac6a5eddd156c776ac75ff54cfe54a5bc.html</anchorfile>
      <anchor>ac6a5eddd156c776ac75ff54cfe54a5bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>const value_type &amp;</type>
      <name>const_reference</name>
      <anchorfile>classnlohmann_1_1basic__json_a4057c5425f4faacfe39a8046871786ca.html</anchorfile>
      <anchor>a4057c5425f4faacfe39a8046871786ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::ptrdiff_t</type>
      <name>difference_type</name>
      <anchorfile>classnlohmann_1_1basic__json_afe7c1303357e19cea9527af4e9a31d8f.html</anchorfile>
      <anchor>afe7c1303357e19cea9527af4e9a31d8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::size_t</type>
      <name>size_type</name>
      <anchorfile>classnlohmann_1_1basic__json_a39f2cd0b58106097e0e67bf185cc519b.html</anchorfile>
      <anchor>a39f2cd0b58106097e0e67bf185cc519b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>AllocatorType&lt; basic_json &gt;</type>
      <name>allocator_type</name>
      <anchorfile>classnlohmann_1_1basic__json_a86ce930490cf7773b26f5ef49c04a350.html</anchorfile>
      <anchor>a86ce930490cf7773b26f5ef49c04a350</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::allocator_traits&lt; allocator_type &gt;::pointer</type>
      <name>pointer</name>
      <anchorfile>classnlohmann_1_1basic__json_aefee1f777198c68724bd127e0c8abbe4.html</anchorfile>
      <anchor>aefee1f777198c68724bd127e0c8abbe4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::allocator_traits&lt; allocator_type &gt;::const_pointer</type>
      <name>const_pointer</name>
      <anchorfile>classnlohmann_1_1basic__json_aff3d5cd2a75612364b888d8693231b58.html</anchorfile>
      <anchor>aff3d5cd2a75612364b888d8693231b58</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>iter_impl&lt; basic_json &gt;</type>
      <name>iterator</name>
      <anchorfile>classnlohmann_1_1basic__json_a099316232c76c034030a38faa6e34dca.html</anchorfile>
      <anchor>a099316232c76c034030a38faa6e34dca</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>iter_impl&lt; const basic_json &gt;</type>
      <name>const_iterator</name>
      <anchorfile>classnlohmann_1_1basic__json_a41a70cf9993951836d129bb1c2b3126a.html</anchorfile>
      <anchor>a41a70cf9993951836d129bb1c2b3126a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>json_reverse_iterator&lt; typename basic_json::iterator &gt;</type>
      <name>reverse_iterator</name>
      <anchorfile>classnlohmann_1_1basic__json_ac223d5560c2b05a208c88de67376c5f2.html</anchorfile>
      <anchor>ac223d5560c2b05a208c88de67376c5f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>json_reverse_iterator&lt; typename basic_json::const_iterator &gt;</type>
      <name>const_reverse_iterator</name>
      <anchorfile>classnlohmann_1_1basic__json_a72be3c24bfa24f0993d6c11af03e7404.html</anchorfile>
      <anchor>a72be3c24bfa24f0993d6c11af03e7404</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::less&lt; StringType &gt;</type>
      <name>object_comparator_t</name>
      <anchorfile>classnlohmann_1_1basic__json_abed9e77c5fcfc925fcdd489911069c3b.html</anchorfile>
      <anchor>abed9e77c5fcfc925fcdd489911069c3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ObjectType&lt; StringType, basic_json, object_comparator_t, AllocatorType&lt; std::pair&lt; const StringType, basic_json &gt; &gt;&gt;</type>
      <name>object_t</name>
      <anchorfile>classnlohmann_1_1basic__json_a5e48a7893520e1314bf0c9723e26ea2a.html</anchorfile>
      <anchor>a5e48a7893520e1314bf0c9723e26ea2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ArrayType&lt; basic_json, AllocatorType&lt; basic_json &gt; &gt;</type>
      <name>array_t</name>
      <anchorfile>classnlohmann_1_1basic__json_ae095578e03df97c5b3991787f1056374.html</anchorfile>
      <anchor>ae095578e03df97c5b3991787f1056374</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>StringType</type>
      <name>string_t</name>
      <anchorfile>classnlohmann_1_1basic__json_a61f8566a1a85a424c7266fb531dca005.html</anchorfile>
      <anchor>a61f8566a1a85a424c7266fb531dca005</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>BooleanType</type>
      <name>boolean_t</name>
      <anchorfile>classnlohmann_1_1basic__json_a4c919102a9b4fe0d588af64801436082.html</anchorfile>
      <anchor>a4c919102a9b4fe0d588af64801436082</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>NumberIntegerType</type>
      <name>number_integer_t</name>
      <anchorfile>classnlohmann_1_1basic__json_a98e611d67b7bd75307de99c9358ab2dc.html</anchorfile>
      <anchor>a98e611d67b7bd75307de99c9358ab2dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>NumberUnsignedType</type>
      <name>number_unsigned_t</name>
      <anchorfile>classnlohmann_1_1basic__json_ab906e29b5d83ac162e823ada2156b989.html</anchorfile>
      <anchor>ab906e29b5d83ac162e823ada2156b989</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>NumberFloatType</type>
      <name>number_float_t</name>
      <anchorfile>classnlohmann_1_1basic__json_a88d6103cb3620410b35200ee8e313d97.html</anchorfile>
      <anchor>a88d6103cb3620410b35200ee8e313d97</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>array</name>
      <anchorfile>classnlohmann_1_1basic__json_a8a7d537fc297bbc5b845f92fe0445e3b.html</anchorfile>
      <anchor>a8a7d537fc297bbc5b845f92fe0445e3b</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(initializer_list_t init={})</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>object</name>
      <anchorfile>classnlohmann_1_1basic__json_a31f84ee15c4690ff705bed74736d04c6.html</anchorfile>
      <anchor>a31f84ee15c4690ff705bed74736d04c6</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(initializer_list_t init={})</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>basic_json</name>
      <anchorfile>classnlohmann_1_1basic__json_aed115142bd0c6c66c864700e0467df55.html</anchorfile>
      <anchor>aed115142bd0c6c66c864700e0467df55</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json@F@basic_json#1$@N@nlohmann@N@detail@E@value_t#</clangid>
      <arglist>(const value_t v)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>basic_json</name>
      <anchorfile>classnlohmann_1_1basic__json_ae9be9e956bfc4658f35d17c6aa72b063.html</anchorfile>
      <anchor>ae9be9e956bfc4658f35d17c6aa72b063</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json@F@basic_json#I#</clangid>
      <arglist>(std::nullptr_t=nullptr) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>basic_json</name>
      <anchorfile>classnlohmann_1_1basic__json_a7639e0834df2bc719a04ffea89b31abc.html</anchorfile>
      <anchor>a7639e0834df2bc719a04ffea89b31abc</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json@FT@&gt;3#T#T#NIbasic_json#&amp;&amp;t1.0#v#</clangid>
      <arglist>(CompatibleType &amp;&amp;val) noexcept(noexcept(JSONSerializer&lt; U &gt;::to_json(std::declval&lt; basic_json_t &amp; &gt;(), std::forward&lt; CompatibleType &gt;(val))))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>basic_json</name>
      <anchorfile>classnlohmann_1_1basic__json_aa16dc469c842fa8a0aaf6f5a95c46bb3.html</anchorfile>
      <anchor>aa16dc469c842fa8a0aaf6f5a95c46bb3</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(const BasicJsonType &amp;val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>basic_json</name>
      <anchorfile>classnlohmann_1_1basic__json_ab5dfd9a2b2663b219641cb7fe59b6da2.html</anchorfile>
      <anchor>ab5dfd9a2b2663b219641cb7fe59b6da2</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(initializer_list_t init, bool type_deduction=true, value_t manual_type=value_t::array)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>basic_json</name>
      <anchorfile>classnlohmann_1_1basic__json_ab6816ae5100409254ed0a8bc21c387bb.html</anchorfile>
      <anchor>ab6816ae5100409254ed0a8bc21c387bb</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(size_type cnt, const basic_json &amp;val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>basic_json</name>
      <anchorfile>classnlohmann_1_1basic__json_abe197e9f3184487805cfb5bba6fd5938.html</anchorfile>
      <anchor>abe197e9f3184487805cfb5bba6fd5938</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(InputIT first, InputIT last)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>basic_json</name>
      <anchorfile>classnlohmann_1_1basic__json_af5de621bcf646c332343f9c1e011126c.html</anchorfile>
      <anchor>af5de621bcf646c332343f9c1e011126c</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(const basic_json &amp;other)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>basic_json</name>
      <anchorfile>classnlohmann_1_1basic__json_a9a06d1efd50a00f4889f831f851ce124.html</anchorfile>
      <anchor>a9a06d1efd50a00f4889f831f851ce124</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(basic_json &amp;&amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>basic_json &amp;</type>
      <name>operator=</name>
      <anchorfile>classnlohmann_1_1basic__json_a849368ca71af3a93d576939d486f61c7.html</anchorfile>
      <anchor>a849368ca71af3a93d576939d486f61c7</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(basic_json other) noexcept(std::is_nothrow_move_constructible&lt; value_t &gt;::value and std::is_nothrow_move_assignable&lt; value_t &gt;::value and std::is_nothrow_move_constructible&lt; json_value &gt;::value and std::is_nothrow_move_assignable&lt; json_value &gt;::value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~basic_json</name>
      <anchorfile>classnlohmann_1_1basic__json_aba01953d5d90e676d504863b8d9fdde5.html</anchorfile>
      <anchor>aba01953d5d90e676d504863b8d9fdde5</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>string_t</type>
      <name>dump</name>
      <anchorfile>classnlohmann_1_1basic__json_a50ec80b02d0f3f51130d4abb5d1cfdc5.html</anchorfile>
      <anchor>a50ec80b02d0f3f51130d4abb5d1cfdc5</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(const int indent=-1, const char indent_char=&apos; &apos;, const bool ensure_ascii=false, const error_handler_t error_handler=error_handler_t::strict) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr value_t</type>
      <name>type</name>
      <anchorfile>classnlohmann_1_1basic__json_a2b2d781d7f2a4ee41bc0016e931cadf7.html</anchorfile>
      <anchor>a2b2d781d7f2a4ee41bc0016e931cadf7</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_primitive</name>
      <anchorfile>classnlohmann_1_1basic__json_a6362b88718eb5c6d4fed6a61eed44b95.html</anchorfile>
      <anchor>a6362b88718eb5c6d4fed6a61eed44b95</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_structured</name>
      <anchorfile>classnlohmann_1_1basic__json_a9f68a0af820c3ced7f9d17851ce4c22d.html</anchorfile>
      <anchor>a9f68a0af820c3ced7f9d17851ce4c22d</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_null</name>
      <anchorfile>classnlohmann_1_1basic__json_a8faa039ca82427ed29c486ffd00600c3.html</anchorfile>
      <anchor>a8faa039ca82427ed29c486ffd00600c3</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_boolean</name>
      <anchorfile>classnlohmann_1_1basic__json_a943e8cb182d0f2365c76d64b42eaa6fd.html</anchorfile>
      <anchor>a943e8cb182d0f2365c76d64b42eaa6fd</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_number</name>
      <anchorfile>classnlohmann_1_1basic__json_a2b9852390abb4b1ef5fac6984e2fc0f3.html</anchorfile>
      <anchor>a2b9852390abb4b1ef5fac6984e2fc0f3</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_number_integer</name>
      <anchorfile>classnlohmann_1_1basic__json_abac8af76067f1e8fdca9052882c74428.html</anchorfile>
      <anchor>abac8af76067f1e8fdca9052882c74428</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_number_unsigned</name>
      <anchorfile>classnlohmann_1_1basic__json_abc7378cba0613a78b9aad1c8e7044bb0.html</anchorfile>
      <anchor>abc7378cba0613a78b9aad1c8e7044bb0</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_number_float</name>
      <anchorfile>classnlohmann_1_1basic__json_a33b4bf898b857c962e798fc7f6e86e70.html</anchorfile>
      <anchor>a33b4bf898b857c962e798fc7f6e86e70</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_object</name>
      <anchorfile>classnlohmann_1_1basic__json_af8f511af124e82e4579f444b4175787c.html</anchorfile>
      <anchor>af8f511af124e82e4579f444b4175787c</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_array</name>
      <anchorfile>classnlohmann_1_1basic__json_aef9ce5dd2381caee1f8ddcdb5bdd9c65.html</anchorfile>
      <anchor>aef9ce5dd2381caee1f8ddcdb5bdd9c65</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_string</name>
      <anchorfile>classnlohmann_1_1basic__json_a69b596a4a6683b362095c9a139637396.html</anchorfile>
      <anchor>a69b596a4a6683b362095c9a139637396</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_discarded</name>
      <anchorfile>classnlohmann_1_1basic__json_aabe623bc8304c2ba92d96d91f390fab4.html</anchorfile>
      <anchor>aabe623bc8304c2ba92d96d91f390fab4</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>operator value_t</name>
      <anchorfile>classnlohmann_1_1basic__json_a26ef3058e249f82a04f8ec18f7419027.html</anchorfile>
      <anchor>a26ef3058e249f82a04f8ec18f7419027</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>basic_json</type>
      <name>get</name>
      <anchorfile>classnlohmann_1_1basic__json_a6b187a22994c12c8cae0dd5ee99dc85e.html</anchorfile>
      <anchor>a6b187a22994c12c8cae0dd5ee99dc85e</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>BasicJsonType</type>
      <name>get</name>
      <anchorfile>classnlohmann_1_1basic__json_a30ff63a4d671eb14f652356cd934320c.html</anchorfile>
      <anchor>a30ff63a4d671eb14f652356cd934320c</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>ValueType</type>
      <name>get</name>
      <anchorfile>classnlohmann_1_1basic__json_aa6602bb24022183ab989439e19345d08.html</anchorfile>
      <anchor>aa6602bb24022183ab989439e19345d08</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept(noexcept(JSONSerializer&lt; ValueType &gt;::from_json(std::declval&lt; const basic_json_t &amp; &gt;(), std::declval&lt; ValueType &amp; &gt;())))</arglist>
    </member>
    <member kind="function">
      <type>ValueType</type>
      <name>get</name>
      <anchorfile>classnlohmann_1_1basic__json_a5afa21d477e13fa7a3dcd7ea66c48b52.html</anchorfile>
      <anchor>a5afa21d477e13fa7a3dcd7ea66c48b52</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept(noexcept(JSONSerializer&lt; ValueTypeCV &gt;::from_json(std::declval&lt; const basic_json_t &amp; &gt;())))</arglist>
    </member>
    <member kind="function">
      <type>ValueType &amp;</type>
      <name>get_to</name>
      <anchorfile>classnlohmann_1_1basic__json_a65753c68f06639eda0d355f919564e01.html</anchorfile>
      <anchor>a65753c68f06639eda0d355f919564e01</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(ValueType &amp;v) const noexcept(noexcept(JSONSerializer&lt; ValueType &gt;::from_json(std::declval&lt; const basic_json_t &amp; &gt;(), v)))</arglist>
    </member>
    <member kind="function">
      <type>Array</type>
      <name>get_to</name>
      <anchorfile>classnlohmann_1_1basic__json_ab9d91cc9c3b62782b38d8f2158269937.html</anchorfile>
      <anchor>ab9d91cc9c3b62782b38d8f2158269937</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(T(&amp;v)[N]) const noexcept(noexcept(JSONSerializer&lt; Array &gt;::from_json(std::declval&lt; const basic_json_t &amp; &gt;(), v)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>get_ptr</name>
      <anchorfile>classnlohmann_1_1basic__json_abefbb319df8ed4f8705b4fd4e4dc731c.html</anchorfile>
      <anchor>abefbb319df8ed4f8705b4fd4e4dc731c</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() noexcept -&gt; decltype(std::declval&lt; basic_json_t &amp; &gt;().get_impl_ptr(std::declval&lt; PointerType &gt;()))</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>get_ptr</name>
      <anchorfile>classnlohmann_1_1basic__json_a6508b9ef55eb018231fb2198211f6d73.html</anchorfile>
      <anchor>a6508b9ef55eb018231fb2198211f6d73</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept -&gt; decltype(std::declval&lt; const basic_json_t &amp; &gt;().get_impl_ptr(std::declval&lt; PointerType &gt;()))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>get</name>
      <anchorfile>classnlohmann_1_1basic__json_a44516cba796e50ce5d62c9d6b7ab4c1d.html</anchorfile>
      <anchor>a44516cba796e50ce5d62c9d6b7ab4c1d</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() noexcept -&gt; decltype(std::declval&lt; basic_json_t &amp; &gt;().template get_ptr&lt; PointerType &gt;())</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>get</name>
      <anchorfile>classnlohmann_1_1basic__json_ad6b0b151621542e5d135812b8c163222.html</anchorfile>
      <anchor>ad6b0b151621542e5d135812b8c163222</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const noexcept -&gt; decltype(std::declval&lt; const basic_json_t &amp; &gt;().template get_ptr&lt; PointerType &gt;())</arglist>
    </member>
    <member kind="function">
      <type>ReferenceType</type>
      <name>get_ref</name>
      <anchorfile>classnlohmann_1_1basic__json_afbd800010b67619463c0fce6e74f7878.html</anchorfile>
      <anchor>afbd800010b67619463c0fce6e74f7878</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ReferenceType</type>
      <name>get_ref</name>
      <anchorfile>classnlohmann_1_1basic__json_ac382f3d2bc6a5d52d936e4e40593f03b.html</anchorfile>
      <anchor>ac382f3d2bc6a5d52d936e4e40593f03b</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator ValueType</name>
      <anchorfile>classnlohmann_1_1basic__json_a1f1d4bc973c5b866db3d96e14d2c9f3f.html</anchorfile>
      <anchor>a1f1d4bc973c5b866db3d96e14d2c9f3f</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>at</name>
      <anchorfile>classnlohmann_1_1basic__json_a73ae333487310e3302135189ce8ff5d8.html</anchorfile>
      <anchor>a73ae333487310e3302135189ce8ff5d8</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(size_type idx)</arglist>
    </member>
    <member kind="function">
      <type>const_reference</type>
      <name>at</name>
      <anchorfile>classnlohmann_1_1basic__json_ab157adb4de8475b452da9ebf04f2de15.html</anchorfile>
      <anchor>ab157adb4de8475b452da9ebf04f2de15</anchor>
      <arglist>(size_type idx) const</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>at</name>
      <anchorfile>classnlohmann_1_1basic__json_a93403e803947b86f4da2d1fb3345cf2c.html</anchorfile>
      <anchor>a93403e803947b86f4da2d1fb3345cf2c</anchor>
      <arglist>(const typename object_t::key_type &amp;key)</arglist>
    </member>
    <member kind="function">
      <type>const_reference</type>
      <name>at</name>
      <anchorfile>classnlohmann_1_1basic__json_acac9d438c9bb12740dcdb01069293a34.html</anchorfile>
      <anchor>acac9d438c9bb12740dcdb01069293a34</anchor>
      <arglist>(const typename object_t::key_type &amp;key) const</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>operator[]</name>
      <anchorfile>classnlohmann_1_1basic__json_ac871e3b03fb2eeca9a8de4db2bea760f.html</anchorfile>
      <anchor>ac871e3b03fb2eeca9a8de4db2bea760f</anchor>
      <arglist>(size_type idx)</arglist>
    </member>
    <member kind="function">
      <type>const_reference</type>
      <name>operator[]</name>
      <anchorfile>classnlohmann_1_1basic__json_a9cb592cd85c14f3e845e30d51cf17efb.html</anchorfile>
      <anchor>a9cb592cd85c14f3e845e30d51cf17efb</anchor>
      <arglist>(size_type idx) const</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>operator[]</name>
      <anchorfile>classnlohmann_1_1basic__json_a233b02b0839ef798942dd46157cc0fe6.html</anchorfile>
      <anchor>a233b02b0839ef798942dd46157cc0fe6</anchor>
      <arglist>(const typename object_t::key_type &amp;key)</arglist>
    </member>
    <member kind="function">
      <type>const_reference</type>
      <name>operator[]</name>
      <anchorfile>classnlohmann_1_1basic__json_ab2318780e5ae692039e816b6ac32c91e.html</anchorfile>
      <anchor>ab2318780e5ae692039e816b6ac32c91e</anchor>
      <arglist>(const typename object_t::key_type &amp;key) const</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>operator[]</name>
      <anchorfile>classnlohmann_1_1basic__json_abb8eaa633584b5aff9c8fcd242f25ca8.html</anchorfile>
      <anchor>abb8eaa633584b5aff9c8fcd242f25ca8</anchor>
      <arglist>(T *key)</arglist>
    </member>
    <member kind="function">
      <type>const_reference</type>
      <name>operator[]</name>
      <anchorfile>classnlohmann_1_1basic__json_a26554213cbb1722accc460ce348c860a.html</anchorfile>
      <anchor>a26554213cbb1722accc460ce348c860a</anchor>
      <arglist>(T *key) const</arglist>
    </member>
    <member kind="function">
      <type>ValueType</type>
      <name>value</name>
      <anchorfile>classnlohmann_1_1basic__json_adcf8ca5079f5db993820bf50036bf45d.html</anchorfile>
      <anchor>adcf8ca5079f5db993820bf50036bf45d</anchor>
      <arglist>(const typename object_t::key_type &amp;key, const ValueType &amp;default_value) const</arglist>
    </member>
    <member kind="function">
      <type>string_t</type>
      <name>value</name>
      <anchorfile>classnlohmann_1_1basic__json_ad6a18403e7fbac9c4efd06facc71fc88.html</anchorfile>
      <anchor>ad6a18403e7fbac9c4efd06facc71fc88</anchor>
      <arglist>(const typename object_t::key_type &amp;key, const char *default_value) const</arglist>
    </member>
    <member kind="function">
      <type>ValueType</type>
      <name>value</name>
      <anchorfile>classnlohmann_1_1basic__json_a671aea68432ecb28770bbc482918f023.html</anchorfile>
      <anchor>a671aea68432ecb28770bbc482918f023</anchor>
      <arglist>(const json_pointer &amp;ptr, const ValueType &amp;default_value) const</arglist>
    </member>
    <member kind="function">
      <type>string_t</type>
      <name>value</name>
      <anchorfile>classnlohmann_1_1basic__json_a869c900ee02cf1a68988dcce3b375424.html</anchorfile>
      <anchor>a869c900ee02cf1a68988dcce3b375424</anchor>
      <arglist>(const json_pointer &amp;ptr, const char *default_value) const</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>front</name>
      <anchorfile>classnlohmann_1_1basic__json_a3acba9c6ceb7214e565fe08c3ba5b352.html</anchorfile>
      <anchor>a3acba9c6ceb7214e565fe08c3ba5b352</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_reference</type>
      <name>front</name>
      <anchorfile>classnlohmann_1_1basic__json_a4b1fb3671ade9afc8d33b2c9510acbfc.html</anchorfile>
      <anchor>a4b1fb3671ade9afc8d33b2c9510acbfc</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>back</name>
      <anchorfile>classnlohmann_1_1basic__json_a011397134847f36db0ed7d7a93753677.html</anchorfile>
      <anchor>a011397134847f36db0ed7d7a93753677</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_reference</type>
      <name>back</name>
      <anchorfile>classnlohmann_1_1basic__json_a83fe4a151b3a591f357527d5d9aa1b9f.html</anchorfile>
      <anchor>a83fe4a151b3a591f357527d5d9aa1b9f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>IteratorType</type>
      <name>erase</name>
      <anchorfile>classnlohmann_1_1basic__json_a068a16e76be178e83da6a192916923ed.html</anchorfile>
      <anchor>a068a16e76be178e83da6a192916923ed</anchor>
      <arglist>(IteratorType pos)</arglist>
    </member>
    <member kind="function">
      <type>IteratorType</type>
      <name>erase</name>
      <anchorfile>classnlohmann_1_1basic__json_a4b3f7eb2d4625d95a51fbbdceb7c5f39.html</anchorfile>
      <anchor>a4b3f7eb2d4625d95a51fbbdceb7c5f39</anchor>
      <arglist>(IteratorType first, IteratorType last)</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>erase</name>
      <anchorfile>classnlohmann_1_1basic__json_a2f8484d69c55d8f2a9697a7bec29362a.html</anchorfile>
      <anchor>a2f8484d69c55d8f2a9697a7bec29362a</anchor>
      <arglist>(const typename object_t::key_type &amp;key)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>erase</name>
      <anchorfile>classnlohmann_1_1basic__json_a88cbcefe9a3f4d294bed0653550a5cb9.html</anchorfile>
      <anchor>a88cbcefe9a3f4d294bed0653550a5cb9</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(const size_type idx)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>find</name>
      <anchorfile>classnlohmann_1_1basic__json_a89eb3928f57903677051c80534be9cb1.html</anchorfile>
      <anchor>a89eb3928f57903677051c80534be9cb1</anchor>
      <arglist>(KeyT &amp;&amp;key)</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>find</name>
      <anchorfile>classnlohmann_1_1basic__json_ae625a0647486edf2bb38c849ca67f934.html</anchorfile>
      <anchor>ae625a0647486edf2bb38c849ca67f934</anchor>
      <arglist>(KeyT &amp;&amp;key) const</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>count</name>
      <anchorfile>classnlohmann_1_1basic__json_a0d74bfcf65662f1d66d14c34b0027098.html</anchorfile>
      <anchor>a0d74bfcf65662f1d66d14c34b0027098</anchor>
      <arglist>(KeyT &amp;&amp;key) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>contains</name>
      <anchorfile>classnlohmann_1_1basic__json_a9286acdc0578fc66e9346323e69fc0e3.html</anchorfile>
      <anchor>a9286acdc0578fc66e9346323e69fc0e3</anchor>
      <arglist>(KeyT &amp;&amp;key) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>contains</name>
      <anchorfile>classnlohmann_1_1basic__json_ab23b04802eb9da97dc3f664e54e09cb3.html</anchorfile>
      <anchor>ab23b04802eb9da97dc3f664e54e09cb3</anchor>
      <arglist>(const json_pointer &amp;ptr) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static iteration_proxy&lt; iterator &gt;</type>
      <name>iterator_wrapper</name>
      <anchorfile>classnlohmann_1_1basic__json_a5e4212986136ca1220f351c60e89906b.html</anchorfile>
      <anchor>a5e4212986136ca1220f351c60e89906b</anchor>
      <arglist>(reference ref) noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static iteration_proxy&lt; const_iterator &gt;</type>
      <name>iterator_wrapper</name>
      <anchorfile>classnlohmann_1_1basic__json_a4d8795ce15be7ce2a95260663bde640d.html</anchorfile>
      <anchor>a4d8795ce15be7ce2a95260663bde640d</anchor>
      <arglist>(const_reference ref) noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classnlohmann_1_1basic__json_a0ff28dac23f2bdecee9564d07f51dcdc.html</anchorfile>
      <anchor>a0ff28dac23f2bdecee9564d07f51dcdc</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classnlohmann_1_1basic__json_a4f0f5dd42b2987ff20306ed78bd31d1d.html</anchorfile>
      <anchor>a4f0f5dd42b2987ff20306ed78bd31d1d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>cbegin</name>
      <anchorfile>classnlohmann_1_1basic__json_ad865d6c291b237ae508d5cb2146b5877.html</anchorfile>
      <anchor>ad865d6c291b237ae508d5cb2146b5877</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classnlohmann_1_1basic__json_a13e032a02a7fd8a93fdddc2fcbc4763c.html</anchorfile>
      <anchor>a13e032a02a7fd8a93fdddc2fcbc4763c</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classnlohmann_1_1basic__json_a1c15707055088cd5436ae91db72cbe67.html</anchorfile>
      <anchor>a1c15707055088cd5436ae91db72cbe67</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>cend</name>
      <anchorfile>classnlohmann_1_1basic__json_a8dba7b7d2f38e6b0c614030aa43983f6.html</anchorfile>
      <anchor>a8dba7b7d2f38e6b0c614030aa43983f6</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classnlohmann_1_1basic__json_a1ef93e2006dbe52667294f5ef38b0b10.html</anchorfile>
      <anchor>a1ef93e2006dbe52667294f5ef38b0b10</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classnlohmann_1_1basic__json_a515e7618392317dbf4b72d3e18bf2ab2.html</anchorfile>
      <anchor>a515e7618392317dbf4b72d3e18bf2ab2</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classnlohmann_1_1basic__json_ac77aed0925d447744676725ab0b6d535.html</anchorfile>
      <anchor>ac77aed0925d447744676725ab0b6d535</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classnlohmann_1_1basic__json_a4f73d4cee67ea328d785979c22af0ae1.html</anchorfile>
      <anchor>a4f73d4cee67ea328d785979c22af0ae1</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>crbegin</name>
      <anchorfile>classnlohmann_1_1basic__json_a1e0769d22d54573f294da0e5c6abc9de.html</anchorfile>
      <anchor>a1e0769d22d54573f294da0e5c6abc9de</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>crend</name>
      <anchorfile>classnlohmann_1_1basic__json_a5795b029dbf28e0cb2c7a439ec5d0a88.html</anchorfile>
      <anchor>a5795b029dbf28e0cb2c7a439ec5d0a88</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iteration_proxy&lt; iterator &gt;</type>
      <name>items</name>
      <anchorfile>classnlohmann_1_1basic__json_afe3e137ace692efa08590d8df40f58dd.html</anchorfile>
      <anchor>afe3e137ace692efa08590d8df40f58dd</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>iteration_proxy&lt; const_iterator &gt;</type>
      <name>items</name>
      <anchorfile>classnlohmann_1_1basic__json_a71dd7adfca43660c10e6624f4b5c290c.html</anchorfile>
      <anchor>a71dd7adfca43660c10e6624f4b5c290c</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>empty</name>
      <anchorfile>classnlohmann_1_1basic__json_a1a86d444bfeaa9518d2421aedd74444a.html</anchorfile>
      <anchor>a1a86d444bfeaa9518d2421aedd74444a</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>size</name>
      <anchorfile>classnlohmann_1_1basic__json_a25e27ad0c6d53c01871c5485e1f75b96.html</anchorfile>
      <anchor>a25e27ad0c6d53c01871c5485e1f75b96</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>size_type</type>
      <name>max_size</name>
      <anchorfile>classnlohmann_1_1basic__json_a2f47d3c6a441c57dd2be00449fbb88e1.html</anchorfile>
      <anchor>a2f47d3c6a441c57dd2be00449fbb88e1</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>classnlohmann_1_1basic__json_abfeba47810ca72f2176419942c4e1952.html</anchorfile>
      <anchor>abfeba47810ca72f2176419942c4e1952</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push_back</name>
      <anchorfile>classnlohmann_1_1basic__json_ac8e523ddc8c2dd7e5d2daf0d49a9c0d7.html</anchorfile>
      <anchor>ac8e523ddc8c2dd7e5d2daf0d49a9c0d7</anchor>
      <arglist>(basic_json &amp;&amp;val)</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>operator+=</name>
      <anchorfile>classnlohmann_1_1basic__json_aea1085f2d35cc0e1ce119cf0110119e6.html</anchorfile>
      <anchor>aea1085f2d35cc0e1ce119cf0110119e6</anchor>
      <arglist>(basic_json &amp;&amp;val)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push_back</name>
      <anchorfile>classnlohmann_1_1basic__json_ab4384af330b79de0e5f279576803a2c7.html</anchorfile>
      <anchor>ab4384af330b79de0e5f279576803a2c7</anchor>
      <arglist>(const basic_json &amp;val)</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>operator+=</name>
      <anchorfile>classnlohmann_1_1basic__json_adc29dd6358ff7a9062d7e168c24e7484.html</anchorfile>
      <anchor>adc29dd6358ff7a9062d7e168c24e7484</anchor>
      <arglist>(const basic_json &amp;val)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push_back</name>
      <anchorfile>classnlohmann_1_1basic__json_ae11a3a51782c058fff2f6550cdfb9b3c.html</anchorfile>
      <anchor>ae11a3a51782c058fff2f6550cdfb9b3c</anchor>
      <arglist>(const typename object_t::value_type &amp;val)</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>operator+=</name>
      <anchorfile>classnlohmann_1_1basic__json_abf04978d85a2d5c4754f4806d42f46fd.html</anchorfile>
      <anchor>abf04978d85a2d5c4754f4806d42f46fd</anchor>
      <arglist>(const typename object_t::value_type &amp;val)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push_back</name>
      <anchorfile>classnlohmann_1_1basic__json_a1be31ef2d2934d37a818083a4af44f99.html</anchorfile>
      <anchor>a1be31ef2d2934d37a818083a4af44f99</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist>(initializer_list_t init)</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>operator+=</name>
      <anchorfile>classnlohmann_1_1basic__json_af245c2b6714d76ed99a2d02f2596d596.html</anchorfile>
      <anchor>af245c2b6714d76ed99a2d02f2596d596</anchor>
      <arglist>(initializer_list_t init)</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>emplace_back</name>
      <anchorfile>classnlohmann_1_1basic__json_abf29131f898b05aad2c01a9c80e7a002.html</anchorfile>
      <anchor>abf29131f898b05aad2c01a9c80e7a002</anchor>
      <arglist>(Args &amp;&amp;... args)</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; iterator, bool &gt;</type>
      <name>emplace</name>
      <anchorfile>classnlohmann_1_1basic__json_a5338e282d1d02bed389d852dd670d98d.html</anchorfile>
      <anchor>a5338e282d1d02bed389d852dd670d98d</anchor>
      <arglist>(Args &amp;&amp;... args)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert_iterator</name>
      <anchorfile>classnlohmann_1_1basic__json_a316663487f1d20c0cf349b23f9494bda.html</anchorfile>
      <anchor>a316663487f1d20c0cf349b23f9494bda</anchor>
      <arglist>(const_iterator pos, Args &amp;&amp;... args)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert</name>
      <anchorfile>classnlohmann_1_1basic__json_a0136728f5db69d4051c77b94307abd6c.html</anchorfile>
      <anchor>a0136728f5db69d4051c77b94307abd6c</anchor>
      <arglist>(const_iterator pos, const basic_json &amp;val)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert</name>
      <anchorfile>classnlohmann_1_1basic__json_a1ecce113ff11dd294689ee4d45cbb855.html</anchorfile>
      <anchor>a1ecce113ff11dd294689ee4d45cbb855</anchor>
      <arglist>(const_iterator pos, basic_json &amp;&amp;val)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert</name>
      <anchorfile>classnlohmann_1_1basic__json_a30a7cc24f2931c20ecae37ec4a5e901f.html</anchorfile>
      <anchor>a30a7cc24f2931c20ecae37ec4a5e901f</anchor>
      <arglist>(const_iterator pos, size_type cnt, const basic_json &amp;val)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert</name>
      <anchorfile>classnlohmann_1_1basic__json_a404cfe1bdbf1dc6b229627fcf2afb95f.html</anchorfile>
      <anchor>a404cfe1bdbf1dc6b229627fcf2afb95f</anchor>
      <arglist>(const_iterator pos, const_iterator first, const_iterator last)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert</name>
      <anchorfile>classnlohmann_1_1basic__json_aa19b9b9ca6967295b102f1cc487b1ad7.html</anchorfile>
      <anchor>aa19b9b9ca6967295b102f1cc487b1ad7</anchor>
      <arglist>(const_iterator pos, initializer_list_t ilist)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>insert</name>
      <anchorfile>classnlohmann_1_1basic__json_a1b0a4e60d56f1fe80501ed941e122892.html</anchorfile>
      <anchor>a1b0a4e60d56f1fe80501ed941e122892</anchor>
      <arglist>(const_iterator first, const_iterator last)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>classnlohmann_1_1basic__json_a1cfa9ae5e7c2434cab4cfe69bffffe11.html</anchorfile>
      <anchor>a1cfa9ae5e7c2434cab4cfe69bffffe11</anchor>
      <arglist>(const_reference j)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>classnlohmann_1_1basic__json_a27921dafadb3bbefd180235ec763e3ea.html</anchorfile>
      <anchor>a27921dafadb3bbefd180235ec763e3ea</anchor>
      <arglist>(const_iterator first, const_iterator last)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>classnlohmann_1_1basic__json_a8c9d932353e1ab98a7dc2fc27e002031.html</anchorfile>
      <anchor>a8c9d932353e1ab98a7dc2fc27e002031</anchor>
      <arglist>(reference other) noexcept(std::is_nothrow_move_constructible&lt; value_t &gt;::value and std::is_nothrow_move_assignable&lt; value_t &gt;::value and std::is_nothrow_move_constructible&lt; json_value &gt;::value and std::is_nothrow_move_assignable&lt; json_value &gt;::value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>classnlohmann_1_1basic__json_a65b0a24e1361a030ad0a661de22f6c8e.html</anchorfile>
      <anchor>a65b0a24e1361a030ad0a661de22f6c8e</anchor>
      <arglist>(array_t &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>classnlohmann_1_1basic__json_ac31f12587d2f1a3be5ffc394aa9d72a4.html</anchorfile>
      <anchor>ac31f12587d2f1a3be5ffc394aa9d72a4</anchor>
      <arglist>(object_t &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swap</name>
      <anchorfile>classnlohmann_1_1basic__json_adaa1ed0a889d86c8e0216a3d66980f76.html</anchorfile>
      <anchor>adaa1ed0a889d86c8e0216a3d66980f76</anchor>
      <arglist>(string_t &amp;other)</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator==</name>
      <anchorfile>classnlohmann_1_1basic__json_a122640e7e2db1814fc7bbb3c122ec76e.html</anchorfile>
      <anchor>a122640e7e2db1814fc7bbb3c122ec76e</anchor>
      <arglist>(const_reference lhs, const_reference rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator==</name>
      <anchorfile>classnlohmann_1_1basic__json_aba21440ea1aff44f718285ed7d6d20d9.html</anchorfile>
      <anchor>aba21440ea1aff44f718285ed7d6d20d9</anchor>
      <arglist>(const_reference lhs, const ScalarType rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator==</name>
      <anchorfile>classnlohmann_1_1basic__json_aef302e3ae215e46e5035d0e4fdf47235.html</anchorfile>
      <anchor>aef302e3ae215e46e5035d0e4fdf47235</anchor>
      <arglist>(const ScalarType lhs, const_reference rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator!=</name>
      <anchorfile>classnlohmann_1_1basic__json_a6e2e21da48f5d9471716cd868a068327.html</anchorfile>
      <anchor>a6e2e21da48f5d9471716cd868a068327</anchor>
      <arglist>(const_reference lhs, const_reference rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator!=</name>
      <anchorfile>classnlohmann_1_1basic__json_afefc38fc08bdb7a9a7474b5ab4a1140f.html</anchorfile>
      <anchor>afefc38fc08bdb7a9a7474b5ab4a1140f</anchor>
      <arglist>(const_reference lhs, const ScalarType rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator!=</name>
      <anchorfile>classnlohmann_1_1basic__json_ab0e886db6e9fa91ff9fd853333fed05b.html</anchorfile>
      <anchor>ab0e886db6e9fa91ff9fd853333fed05b</anchor>
      <arglist>(const ScalarType lhs, const_reference rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&lt;</name>
      <anchorfile>classnlohmann_1_1basic__json_aacd442b66140c764c594ac8ad7dfd5b3.html</anchorfile>
      <anchor>aacd442b66140c764c594ac8ad7dfd5b3</anchor>
      <arglist>(const_reference lhs, const_reference rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&lt;</name>
      <anchorfile>classnlohmann_1_1basic__json_a7999ee3a69a4979d92e98ab1e88c8759.html</anchorfile>
      <anchor>a7999ee3a69a4979d92e98ab1e88c8759</anchor>
      <arglist>(const_reference lhs, const ScalarType rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&lt;</name>
      <anchorfile>classnlohmann_1_1basic__json_abed3e9b4ab75f5bcbd3cd20f5af5cdab.html</anchorfile>
      <anchor>abed3e9b4ab75f5bcbd3cd20f5af5cdab</anchor>
      <arglist>(const ScalarType lhs, const_reference rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classnlohmann_1_1basic__json_a5c8bb5200f5eac10d31e26be46e5b1ac.html</anchorfile>
      <anchor>a5c8bb5200f5eac10d31e26be46e5b1ac</anchor>
      <arglist>(const_reference lhs, const_reference rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classnlohmann_1_1basic__json_a7e368211047f725f333696aefdf39ffd.html</anchorfile>
      <anchor>a7e368211047f725f333696aefdf39ffd</anchor>
      <arglist>(const_reference lhs, const ScalarType rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classnlohmann_1_1basic__json_ad73f88f70fe5acfa521750a8cd710026.html</anchorfile>
      <anchor>ad73f88f70fe5acfa521750a8cd710026</anchor>
      <arglist>(const ScalarType lhs, const_reference rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&gt;</name>
      <anchorfile>classnlohmann_1_1basic__json_a87db51b6b936fb2ea293cdbc8702dcb8.html</anchorfile>
      <anchor>a87db51b6b936fb2ea293cdbc8702dcb8</anchor>
      <arglist>(const_reference lhs, const_reference rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&gt;</name>
      <anchorfile>classnlohmann_1_1basic__json_a412895af9a582869a4d369a64fb1b6d6.html</anchorfile>
      <anchor>a412895af9a582869a4d369a64fb1b6d6</anchor>
      <arglist>(const_reference lhs, const ScalarType rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&gt;</name>
      <anchorfile>classnlohmann_1_1basic__json_a124c319566198d9f092c5bebea46ce77.html</anchorfile>
      <anchor>a124c319566198d9f092c5bebea46ce77</anchor>
      <arglist>(const ScalarType lhs, const_reference rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classnlohmann_1_1basic__json_a74a943800c7f103d0990d7eef82c6453.html</anchorfile>
      <anchor>a74a943800c7f103d0990d7eef82c6453</anchor>
      <arglist>(const_reference lhs, const_reference rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classnlohmann_1_1basic__json_a68e3a92b3d9be1faa05c92d096299189.html</anchorfile>
      <anchor>a68e3a92b3d9be1faa05c92d096299189</anchor>
      <arglist>(const_reference lhs, const ScalarType rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classnlohmann_1_1basic__json_a5ee0e3e8afc7cbd932d6ed66418fa80a.html</anchorfile>
      <anchor>a5ee0e3e8afc7cbd932d6ed66418fa80a</anchor>
      <arglist>(const ScalarType lhs, const_reference rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classnlohmann_1_1basic__json_a5e34c5435e557d0bf666bd7311211405.html</anchorfile>
      <anchor>a5e34c5435e557d0bf666bd7311211405</anchor>
      <arglist>(std::ostream &amp;o, const basic_json &amp;j)</arglist>
    </member>
    <member kind="friend">
      <type>friend std::ostream &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>classnlohmann_1_1basic__json_a34d6a60dd99e9f33b8273a1c8db5669b.html</anchorfile>
      <anchor>a34d6a60dd99e9f33b8273a1c8db5669b</anchor>
      <arglist>(const basic_json &amp;j, std::ostream &amp;o)</arglist>
    </member>
    <member kind="friend">
      <type>friend std::istream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classnlohmann_1_1basic__json_a60ca396028b8d9714c6e10efbf475af6.html</anchorfile>
      <anchor>a60ca396028b8d9714c6e10efbf475af6</anchor>
      <arglist>(basic_json &amp;j, std::istream &amp;i)</arglist>
    </member>
    <member kind="friend">
      <type>friend std::istream &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>classnlohmann_1_1basic__json_aaf363408931d76472ded14017e59c9e8.html</anchorfile>
      <anchor>aaf363408931d76472ded14017e59c9e8</anchor>
      <arglist>(std::istream &amp;i, basic_json &amp;j)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>parse</name>
      <anchorfile>classnlohmann_1_1basic__json_a265a473e939184aa42655c9ccdf34e58.html</anchorfile>
      <anchor>a265a473e939184aa42655c9ccdf34e58</anchor>
      <arglist>(detail::input_adapter &amp;&amp;i, const parser_callback_t cb=nullptr, const bool allow_exceptions=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>accept</name>
      <anchorfile>classnlohmann_1_1basic__json_a875585b0cb6133902066daccd7c9d420.html</anchorfile>
      <anchor>a875585b0cb6133902066daccd7c9d420</anchor>
      <arglist>(detail::input_adapter &amp;&amp;i)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>sax_parse</name>
      <anchorfile>classnlohmann_1_1basic__json_a8a3dd150c2d1f0df3502d937de0871db.html</anchorfile>
      <anchor>a8a3dd150c2d1f0df3502d937de0871db</anchor>
      <arglist>(detail::input_adapter &amp;&amp;i, SAX *sax, input_format_t format=input_format_t::json, const bool strict=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static basic_json</type>
      <name>parse</name>
      <anchorfile>classnlohmann_1_1basic__json_ab330c13ba254ea41fbc1c52c5c610f45.html</anchorfile>
      <anchor>ab330c13ba254ea41fbc1c52c5c610f45</anchor>
      <arglist>(IteratorType first, IteratorType last, const parser_callback_t cb=nullptr, const bool allow_exceptions=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>accept</name>
      <anchorfile>classnlohmann_1_1basic__json_ae797958b922732bf5fc01053d0659c1f.html</anchorfile>
      <anchor>ae797958b922732bf5fc01053d0659c1f</anchor>
      <arglist>(IteratorType first, IteratorType last)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>sax_parse</name>
      <anchorfile>classnlohmann_1_1basic__json_aab9d7f0843a6e8f18eb2ebb944a796bd.html</anchorfile>
      <anchor>aab9d7f0843a6e8f18eb2ebb944a796bd</anchor>
      <arglist>(IteratorType first, IteratorType last, SAX *sax)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; uint8_t &gt;</type>
      <name>to_cbor</name>
      <anchorfile>classnlohmann_1_1basic__json_a2566783e190dec524bf3445b322873b8.html</anchorfile>
      <anchor>a2566783e190dec524bf3445b322873b8</anchor>
      <arglist>(const basic_json &amp;j)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>to_cbor</name>
      <anchorfile>classnlohmann_1_1basic__json_a5d9a89ac7ed08171a22dc6d65d033c09.html</anchorfile>
      <anchor>a5d9a89ac7ed08171a22dc6d65d033c09</anchor>
      <arglist>(const basic_json &amp;j, detail::output_adapter&lt; uint8_t &gt; o)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>to_cbor</name>
      <anchorfile>classnlohmann_1_1basic__json_a6defa7ec3d3ace8f713f001f720182d7.html</anchorfile>
      <anchor>a6defa7ec3d3ace8f713f001f720182d7</anchor>
      <arglist>(const basic_json &amp;j, detail::output_adapter&lt; char &gt; o)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; uint8_t &gt;</type>
      <name>to_msgpack</name>
      <anchorfile>classnlohmann_1_1basic__json_a09ca1dc273d226afe0ca83a9d7438d9c.html</anchorfile>
      <anchor>a09ca1dc273d226afe0ca83a9d7438d9c</anchor>
      <arglist>(const basic_json &amp;j)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>to_msgpack</name>
      <anchorfile>classnlohmann_1_1basic__json_a4ef190107be36fea6b6c63d71d439c99.html</anchorfile>
      <anchor>a4ef190107be36fea6b6c63d71d439c99</anchor>
      <arglist>(const basic_json &amp;j, detail::output_adapter&lt; uint8_t &gt; o)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>to_msgpack</name>
      <anchorfile>classnlohmann_1_1basic__json_a99efe44b502de2762a433ce3688ec2d2.html</anchorfile>
      <anchor>a99efe44b502de2762a433ce3688ec2d2</anchor>
      <arglist>(const basic_json &amp;j, detail::output_adapter&lt; char &gt; o)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; uint8_t &gt;</type>
      <name>to_ubjson</name>
      <anchorfile>classnlohmann_1_1basic__json_ae1ece6c2059114eac10873f13ef19185.html</anchorfile>
      <anchor>ae1ece6c2059114eac10873f13ef19185</anchor>
      <arglist>(const basic_json &amp;j, const bool use_size=false, const bool use_type=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>to_ubjson</name>
      <anchorfile>classnlohmann_1_1basic__json_a480f6d5a30b9627b55831178266575a7.html</anchorfile>
      <anchor>a480f6d5a30b9627b55831178266575a7</anchor>
      <arglist>(const basic_json &amp;j, detail::output_adapter&lt; uint8_t &gt; o, const bool use_size=false, const bool use_type=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>to_ubjson</name>
      <anchorfile>classnlohmann_1_1basic__json_af66db22ad819346a688042a9da68ee5f.html</anchorfile>
      <anchor>af66db22ad819346a688042a9da68ee5f</anchor>
      <arglist>(const basic_json &amp;j, detail::output_adapter&lt; char &gt; o, const bool use_size=false, const bool use_type=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; uint8_t &gt;</type>
      <name>to_bson</name>
      <anchorfile>classnlohmann_1_1basic__json_a8ca5dd4f18b59e7022b04fd9bf7f5176.html</anchorfile>
      <anchor>a8ca5dd4f18b59e7022b04fd9bf7f5176</anchor>
      <arglist>(const basic_json &amp;j)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>to_bson</name>
      <anchorfile>classnlohmann_1_1basic__json_a51df13f73a970da95c3dcb3d47b0c2c4.html</anchorfile>
      <anchor>a51df13f73a970da95c3dcb3d47b0c2c4</anchor>
      <arglist>(const basic_json &amp;j, detail::output_adapter&lt; uint8_t &gt; o)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>to_bson</name>
      <anchorfile>classnlohmann_1_1basic__json_aeb988f5b2148875ed1c9cb32bec156c6.html</anchorfile>
      <anchor>aeb988f5b2148875ed1c9cb32bec156c6</anchor>
      <arglist>(const basic_json &amp;j, detail::output_adapter&lt; char &gt; o)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>from_cbor</name>
      <anchorfile>classnlohmann_1_1basic__json_a1d568ba1bd6978d80db42aa76626e2cf.html</anchorfile>
      <anchor>a1d568ba1bd6978d80db42aa76626e2cf</anchor>
      <arglist>(detail::input_adapter &amp;&amp;i, const bool strict=true, const bool allow_exceptions=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>from_cbor</name>
      <anchorfile>classnlohmann_1_1basic__json_a513d6fb63a0ea53ce6c28c05ce0f26e6.html</anchorfile>
      <anchor>a513d6fb63a0ea53ce6c28c05ce0f26e6</anchor>
      <arglist>(A1 &amp;&amp;a1, A2 &amp;&amp;a2, const bool strict=true, const bool allow_exceptions=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>from_msgpack</name>
      <anchorfile>classnlohmann_1_1basic__json_a11458b7982adba51bc634f2f8c961e9b.html</anchorfile>
      <anchor>a11458b7982adba51bc634f2f8c961e9b</anchor>
      <arglist>(detail::input_adapter &amp;&amp;i, const bool strict=true, const bool allow_exceptions=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>from_msgpack</name>
      <anchorfile>classnlohmann_1_1basic__json_a022b65246f82c87526940248dc9df6f5.html</anchorfile>
      <anchor>a022b65246f82c87526940248dc9df6f5</anchor>
      <arglist>(A1 &amp;&amp;a1, A2 &amp;&amp;a2, const bool strict=true, const bool allow_exceptions=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>from_ubjson</name>
      <anchorfile>classnlohmann_1_1basic__json_a1ed52b463d2ef14c85ed076467168c72.html</anchorfile>
      <anchor>a1ed52b463d2ef14c85ed076467168c72</anchor>
      <arglist>(detail::input_adapter &amp;&amp;i, const bool strict=true, const bool allow_exceptions=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>from_ubjson</name>
      <anchorfile>classnlohmann_1_1basic__json_a46afafed69ed4c8ae797afb8445fd42f.html</anchorfile>
      <anchor>a46afafed69ed4c8ae797afb8445fd42f</anchor>
      <arglist>(A1 &amp;&amp;a1, A2 &amp;&amp;a2, const bool strict=true, const bool allow_exceptions=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>from_bson</name>
      <anchorfile>classnlohmann_1_1basic__json_a0524486cd0b36a47448df882ec0d5e7b.html</anchorfile>
      <anchor>a0524486cd0b36a47448df882ec0d5e7b</anchor>
      <arglist>(detail::input_adapter &amp;&amp;i, const bool strict=true, const bool allow_exceptions=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>from_bson</name>
      <anchorfile>classnlohmann_1_1basic__json_a000cef9f49c8f04319cf98150361d13d.html</anchorfile>
      <anchor>a000cef9f49c8f04319cf98150361d13d</anchor>
      <arglist>(A1 &amp;&amp;a1, A2 &amp;&amp;a2, const bool strict=true, const bool allow_exceptions=true)</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>operator[]</name>
      <anchorfile>classnlohmann_1_1basic__json_ac6946dffeb3be5aa173645f0467a44b3.html</anchorfile>
      <anchor>ac6946dffeb3be5aa173645f0467a44b3</anchor>
      <arglist>(const json_pointer &amp;ptr)</arglist>
    </member>
    <member kind="function">
      <type>const_reference</type>
      <name>operator[]</name>
      <anchorfile>classnlohmann_1_1basic__json_a9d55e3e63b05e03a2b70cea3761f84cb.html</anchorfile>
      <anchor>a9d55e3e63b05e03a2b70cea3761f84cb</anchor>
      <arglist>(const json_pointer &amp;ptr) const</arglist>
    </member>
    <member kind="function">
      <type>reference</type>
      <name>at</name>
      <anchorfile>classnlohmann_1_1basic__json_a8ab61397c10f18b305520da7073b2b45.html</anchorfile>
      <anchor>a8ab61397c10f18b305520da7073b2b45</anchor>
      <arglist>(const json_pointer &amp;ptr)</arglist>
    </member>
    <member kind="function">
      <type>const_reference</type>
      <name>at</name>
      <anchorfile>classnlohmann_1_1basic__json_a7479d686148c26e252781bb32aa5d5c9.html</anchorfile>
      <anchor>a7479d686148c26e252781bb32aa5d5c9</anchor>
      <arglist>(const json_pointer &amp;ptr) const</arglist>
    </member>
    <member kind="function">
      <type>basic_json</type>
      <name>flatten</name>
      <anchorfile>classnlohmann_1_1basic__json_ab838f000d76662917ffd6ec529569e03.html</anchorfile>
      <anchor>ab838f000d76662917ffd6ec529569e03</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>basic_json</type>
      <name>unflatten</name>
      <anchorfile>classnlohmann_1_1basic__json_a74fa3ab2003f2f6f2b69deaafed9126d.html</anchorfile>
      <anchor>a74fa3ab2003f2f6f2b69deaafed9126d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static JSON_HEDLEY_WARN_UNUSED_RESULT basic_json</type>
      <name>diff</name>
      <anchorfile>classnlohmann_1_1basic__json_a9c4f3554773649beef69461a10a3de87.html</anchorfile>
      <anchor>a9c4f3554773649beef69461a10a3de87</anchor>
      <arglist>(const basic_json &amp;source, const basic_json &amp;target, const std::string &amp;path=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>basic_json</type>
      <name>patch</name>
      <anchorfile>classnlohmann_1_1basic__json_a81e0c41a4a9dff4df2f6973f7f8b2a83.html</anchorfile>
      <anchor>a81e0c41a4a9dff4df2f6973f7f8b2a83</anchor>
      <arglist>(const basic_json &amp;json_patch) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>merge_patch</name>
      <anchorfile>classnlohmann_1_1basic__json_a7c43ed2a3004c1fa9543913f37b9fca9.html</anchorfile>
      <anchor>a7c43ed2a3004c1fa9543913f37b9fca9</anchor>
      <arglist>(const basic_json &amp;apply_patch)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; nlohmann::json &gt;</name>
    <filename>structstd_1_1hash_3_01nlohmann_1_1json_01_4.html</filename>
    <member kind="function">
      <type>std::size_t</type>
      <name>operator()</name>
      <anchorfile>structstd_1_1hash_3_01nlohmann_1_1json_01_4_aec1567d1fa47dbe5b77954dce3a55b64.html</anchorfile>
      <anchor>aec1567d1fa47dbe5b77954dce3a55b64</anchor>
      <arglist>(const nlohmann::json &amp;j) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>nlohmann::json_pointer</name>
    <filename>classnlohmann_1_1json__pointer.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>json_pointer</name>
      <anchorfile>classnlohmann_1_1json__pointer_a7f32d7c62841f0c4a6784cf741a6e4f8.html</anchorfile>
      <anchor>a7f32d7c62841f0c4a6784cf741a6e4f8</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer@F@json_pointer#&amp;1I#</clangid>
      <arglist>(const std::string &amp;s=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>back</name>
      <anchorfile>classnlohmann_1_1json__pointer_a6bd5b554c10f15672135c216893eef31.html</anchorfile>
      <anchor>a6bd5b554c10f15672135c216893eef31</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>empty</name>
      <anchorfile>classnlohmann_1_1json__pointer_a649252bda4a2e75a0915b11a25d8bcc3.html</anchorfile>
      <anchor>a649252bda4a2e75a0915b11a25d8bcc3</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator std::string</name>
      <anchorfile>classnlohmann_1_1json__pointer_ae9015c658f99cf3d48a8563accc79988.html</anchorfile>
      <anchor>ae9015c658f99cf3d48a8563accc79988</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>json_pointer &amp;</type>
      <name>operator/=</name>
      <anchorfile>classnlohmann_1_1json__pointer_a7395bd0af29ac23fd3f21543c935cdfa.html</anchorfile>
      <anchor>a7395bd0af29ac23fd3f21543c935cdfa</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>(const json_pointer &amp;ptr)</arglist>
    </member>
    <member kind="function">
      <type>json_pointer &amp;</type>
      <name>operator/=</name>
      <anchorfile>classnlohmann_1_1json__pointer_abdd21567b2b1d69329af0f520335e68b.html</anchorfile>
      <anchor>abdd21567b2b1d69329af0f520335e68b</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>(std::string token)</arglist>
    </member>
    <member kind="function">
      <type>json_pointer &amp;</type>
      <name>operator/=</name>
      <anchorfile>classnlohmann_1_1json__pointer_a64c8401529131bad1e486d91d703795f.html</anchorfile>
      <anchor>a64c8401529131bad1e486d91d703795f</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>(std::size_t array_index)</arglist>
    </member>
    <member kind="function">
      <type>json_pointer</type>
      <name>parent_pointer</name>
      <anchorfile>classnlohmann_1_1json__pointer_afdaacce1edb7145e0434e014f0e8685a.html</anchorfile>
      <anchor>afdaacce1edb7145e0434e014f0e8685a</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pop_back</name>
      <anchorfile>classnlohmann_1_1json__pointer_a4b1ee4d511ca195bed896a3da47e264c.html</anchorfile>
      <anchor>a4b1ee4d511ca195bed896a3da47e264c</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push_back</name>
      <anchorfile>classnlohmann_1_1json__pointer_a697d12b5bd6205f8866691b166b7c7dc.html</anchorfile>
      <anchor>a697d12b5bd6205f8866691b166b7c7dc</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>(const std::string &amp;token)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push_back</name>
      <anchorfile>classnlohmann_1_1json__pointer_ac228b13596d3c34185da9fe61b570194.html</anchorfile>
      <anchor>ac228b13596d3c34185da9fe61b570194</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>(std::string &amp;&amp;token)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>to_string</name>
      <anchorfile>classnlohmann_1_1json__pointer_a3d4b15d32d096e3776c5d2c773b524f5.html</anchorfile>
      <anchor>a3d4b15d32d096e3776c5d2c773b524f5</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer@F@to_string#1</clangid>
      <arglist>() const</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>basic_json</name>
      <anchorfile>classnlohmann_1_1json__pointer_ada3100cdb8700566051828f1355fa745.html</anchorfile>
      <anchor>ada3100cdb8700566051828f1355fa745</anchor>
      <clangid>c:@N@nlohmann@ST&gt;9#t&gt;3#T#T#pT#t&gt;2#T#pT#T#T#T#T#T#t&gt;1#T#t&gt;2#T#T@basic_json</clangid>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend bool</type>
      <name>operator!=</name>
      <anchorfile>classnlohmann_1_1json__pointer_a6779edcf28e6f018a3bbb29c0b4b5e1e.html</anchorfile>
      <anchor>a6779edcf28e6f018a3bbb29c0b4b5e1e</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>(json_pointer const &amp;lhs, json_pointer const &amp;rhs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend json_pointer</type>
      <name>operator/</name>
      <anchorfile>classnlohmann_1_1json__pointer_a90a11fe6c7f37b1746a3ff9cb24b0d53.html</anchorfile>
      <anchor>a90a11fe6c7f37b1746a3ff9cb24b0d53</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>(const json_pointer &amp;lhs, const json_pointer &amp;rhs)</arglist>
    </member>
    <member kind="friend">
      <type>friend json_pointer</type>
      <name>operator/</name>
      <anchorfile>classnlohmann_1_1json__pointer_a926c9065dbed1bedc17857a813f7a46f.html</anchorfile>
      <anchor>a926c9065dbed1bedc17857a813f7a46f</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>(const json_pointer &amp;ptr, std::string token)</arglist>
    </member>
    <member kind="friend">
      <type>friend json_pointer</type>
      <name>operator/</name>
      <anchorfile>classnlohmann_1_1json__pointer_a9f6bc6f4d4668b4e9a19d8b8ac29da4f.html</anchorfile>
      <anchor>a9f6bc6f4d4668b4e9a19d8b8ac29da4f</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>(const json_pointer &amp;ptr, std::size_t array_index)</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend bool</type>
      <name>operator==</name>
      <anchorfile>classnlohmann_1_1json__pointer_a4667ef558c8c3f8a646bfda0c6654653.html</anchorfile>
      <anchor>a4667ef558c8c3f8a646bfda0c6654653</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_pointer</clangid>
      <arglist>(json_pointer const &amp;lhs, json_pointer const &amp;rhs) noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>nlohmann::json_sax</name>
    <filename>structnlohmann_1_1json__sax.html</filename>
    <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax</clangid>
    <templarg></templarg>
    <member kind="typedef">
      <type>typename BasicJsonType::number_float_t</type>
      <name>number_float_t</name>
      <anchorfile>structnlohmann_1_1json__sax_a390c209bffd8c4800c8f3076dc465a20.html</anchorfile>
      <anchor>a390c209bffd8c4800c8f3076dc465a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename BasicJsonType::number_integer_t</type>
      <name>number_integer_t</name>
      <anchorfile>structnlohmann_1_1json__sax_a0cef30121f02b7fee85e9708148ea0aa.html</anchorfile>
      <anchor>a0cef30121f02b7fee85e9708148ea0aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename BasicJsonType::number_unsigned_t</type>
      <name>number_unsigned_t</name>
      <anchorfile>structnlohmann_1_1json__sax_a32028cc056ae0f43aaae331cdbbbf856.html</anchorfile>
      <anchor>a32028cc056ae0f43aaae331cdbbbf856</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename BasicJsonType::string_t</type>
      <name>string_t</name>
      <anchorfile>structnlohmann_1_1json__sax_ae01977a9f3c5b3667b7a2929ed91061e.html</anchorfile>
      <anchor>ae01977a9f3c5b3667b7a2929ed91061e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~json_sax</name>
      <anchorfile>structnlohmann_1_1json__sax_af31bacfa81aa7818d8639d1da65c8eb5.html</anchorfile>
      <anchor>af31bacfa81aa7818d8639d1da65c8eb5</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@~json_sax#</clangid>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>boolean</name>
      <anchorfile>structnlohmann_1_1json__sax_a82ed080814fa656191a537284bb0c575.html</anchorfile>
      <anchor>a82ed080814fa656191a537284bb0c575</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@boolean#b#</clangid>
      <arglist>(bool val)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>end_array</name>
      <anchorfile>structnlohmann_1_1json__sax_a235ee975617f28e6a996d1e36a282312.html</anchorfile>
      <anchor>a235ee975617f28e6a996d1e36a282312</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@end_array#</clangid>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>end_object</name>
      <anchorfile>structnlohmann_1_1json__sax_ad0c722d53ff97be700ccf6a9468bd456.html</anchorfile>
      <anchor>ad0c722d53ff97be700ccf6a9468bd456</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@end_object#</clangid>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>key</name>
      <anchorfile>structnlohmann_1_1json__sax_a2e0c7ecd80b18d18a8cc76f71cfc2028.html</anchorfile>
      <anchor>a2e0c7ecd80b18d18a8cc76f71cfc2028</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@key#&amp;^type-parameter-0-0:::string_t#</clangid>
      <arglist>(string_t &amp;val)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>null</name>
      <anchorfile>structnlohmann_1_1json__sax_a0ad26edef3f8d530dcec3192bba82df6.html</anchorfile>
      <anchor>a0ad26edef3f8d530dcec3192bba82df6</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@null#</clangid>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>number_float</name>
      <anchorfile>structnlohmann_1_1json__sax_ae7c31614e8a82164d2d7f8dbf4671b25.html</anchorfile>
      <anchor>ae7c31614e8a82164d2d7f8dbf4671b25</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@number_float#^type-parameter-0-0:::number_float_t#&amp;1^type-parameter-0-0:::string_t#</clangid>
      <arglist>(number_float_t val, const string_t &amp;s)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>number_integer</name>
      <anchorfile>structnlohmann_1_1json__sax_affa7a78b8e9cc9cc3ac99927143142a5.html</anchorfile>
      <anchor>affa7a78b8e9cc9cc3ac99927143142a5</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@number_integer#^type-parameter-0-0:::number_integer_t#</clangid>
      <arglist>(number_integer_t val)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>number_unsigned</name>
      <anchorfile>structnlohmann_1_1json__sax_ad9b253083e0509923ba195136f49face.html</anchorfile>
      <anchor>ad9b253083e0509923ba195136f49face</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@number_unsigned#^type-parameter-0-0:::number_unsigned_t#</clangid>
      <arglist>(number_unsigned_t val)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>parse_error</name>
      <anchorfile>structnlohmann_1_1json__sax_a60287e3bd85f489e04c83f7e3b76e613.html</anchorfile>
      <anchor>a60287e3bd85f489e04c83f7e3b76e613</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@parse_error#I#&amp;1I#&amp;1$@N@nlohmann@N@detail@S@exception#</clangid>
      <arglist>(std::size_t position, const std::string &amp;last_token, const detail::exception &amp;ex)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>start_array</name>
      <anchorfile>structnlohmann_1_1json__sax_a5c53878cf08d463eb4e7ca0270532572.html</anchorfile>
      <anchor>a5c53878cf08d463eb4e7ca0270532572</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@start_array#I#</clangid>
      <arglist>(std::size_t elements)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>start_object</name>
      <anchorfile>structnlohmann_1_1json__sax_a0671528b0debb5a348169d61f0382a0f.html</anchorfile>
      <anchor>a0671528b0debb5a348169d61f0382a0f</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@start_object#I#</clangid>
      <arglist>(std::size_t elements)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>string</name>
      <anchorfile>structnlohmann_1_1json__sax_a07eab82f6c82d606787eee9ad73d2bda.html</anchorfile>
      <anchor>a07eab82f6c82d606787eee9ad73d2bda</anchor>
      <clangid>c:@N@nlohmann@ST&gt;1#T@json_sax@F@string#&amp;^type-parameter-0-0:::string_t#</clangid>
      <arglist>(string_t &amp;val)=0</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>nlohmann</name>
    <filename>namespacenlohmann.html</filename>
    <clangid>c:@N@nlohmann</clangid>
    <namespace>nlohmann::anonymous_namespace{json.hpp}</namespace>
    <class kind="struct">nlohmann::adl_serializer</class>
    <class kind="class">nlohmann::basic_json</class>
    <class kind="class">nlohmann::json_pointer</class>
    <class kind="struct">nlohmann::json_sax</class>
    <member kind="typedef">
      <type>basic_json&lt;&gt;</type>
      <name>json</name>
      <anchorfile>namespacenlohmann_a2bfd99e845a2e5cd90aeaf1b1431f474.html</anchorfile>
      <anchor>a2bfd99e845a2e5cd90aeaf1b1431f474</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>NLOHMANN_BASIC_JSON_TPL_DECLARATION std::string</type>
      <name>to_string</name>
      <anchorfile>namespacenlohmann_a6ce645a0b8717757e096a5b5773b7a16.html</anchorfile>
      <anchor>a6ce645a0b8717757e096a5b5773b7a16</anchor>
      <arglist>(const NLOHMANN_BASIC_JSON_TPL &amp;j)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>nlohmann::anonymous_namespace{json.hpp}</name>
    <filename>namespacenlohmann_1_1anonymous__namespace_02json_8hpp_03.html</filename>
    <member kind="variable">
      <type>constexpr const auto &amp;</type>
      <name>from_json</name>
      <anchorfile>namespacenlohmann_1_1anonymous__namespace_02json_8hpp_03_a69afe041fa2aeac2239b65ae88b64af8.html</anchorfile>
      <anchor>a69afe041fa2aeac2239b65ae88b64af8</anchor>
      <clangid>c:json.hpp@aN@from_json</clangid>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr const auto &amp;</type>
      <name>to_json</name>
      <anchorfile>namespacenlohmann_1_1anonymous__namespace_02json_8hpp_03_a455d0daa616e67bbb74d81cf3ba15e79.html</anchorfile>
      <anchor>a455d0daa616e67bbb74d81cf3ba15e79</anchor>
      <clangid>c:json.hpp@aN@to_json</clangid>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>md_faq</name>
    <title>FAQ</title>
    <filename>md_faq</filename>
  </compound>
  <compound kind="page">
    <name>md_binary_formats</name>
    <title>Binary formats</title>
    <filename>md_binary_formats</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>JSON for Modern C++</title>
    <filename>index</filename>
  </compound>
</tagfile>
