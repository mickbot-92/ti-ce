      // {"complex"               ,0, _CPLX, _INT_TYPE, T_TYPE_ID},
      //{"Binary"         ,1,_BINARY_OPERATOR , _INT_MUPADOPERATOR ,T_NUMBER},
      //{"DOM_COMPLEX"               ,0, _CPLX, _INT_TYPE, T_TYPE_ID},
      //{"DOM_FLOAT"                ,0, _DOUBLE_, _INT_TYPE, T_TYPE_ID},
      //{"DOM_FUNC"                ,0, _FUNC, _INT_TYPE, T_TYPE_ID},
      //{"DOM_IDENT"            ,0, _IDNT, _INT_TYPE, T_TYPE_ID},
      //{"DOM_INT"               ,0, _ZINT, _INT_TYPE, T_TYPE_ID},
      //{"DOM_LIST"              ,0, _VECT, _INT_TYPE, T_TYPE_ID},
      //{"DOM_LONGFLOAT"                ,0, _REAL, _INT_TYPE, T_TYPE_ID},
      //{"DOM_MAP"               ,0, _MAP, _INT_TYPE, T_TYPE_ID},
      //{"DOM_MATRIX"              ,0, _VECT, _INT_TYPE, T_TYPE_ID},
      //{"DOM_RAT"              ,0, _FRAC, _INT_TYPE, T_TYPE_ID},
      //{"DOM_SERIES"               ,0, _SPOL1, _INT_TYPE, T_TYPE_ID},
      //{"DOM_STRING"                ,0, _STRNG, _INT_TYPE, T_TYPE_ID},
      //{"DOM_SYMBOLIC"              ,0, _SYMB, _INT_TYPE, T_TYPE_ID},
      //{"DOM_int"                  ,0,  _INT_, _INT_TYPE, T_TYPE_ID},
      {"ELSE",0,0,0,T_ELSE},
      {"END",0,0,0,T_BLOC_END},
      {"False",1,0,_INT_BOOLEAN,T_NUMBER},
      {"IFERR",0,0,0,T_IFERR},
      //{"Nary"         ,1,_NARY_OPERATOR , _INT_MUPADOPERATOR ,T_NUMBER},
      //{"Postfix"         ,1,_POSTFIX_OPERATOR , _INT_MUPADOPERATOR ,T_NUMBER},
      //{"Prefix"         ,1,_PREFIX_OPERATOR , _INT_MUPADOPERATOR ,T_NUMBER},
      {"THEN",0,0,0,T_THEN},
      {"True",1,1,_INT_BOOLEAN,T_NUMBER},
      {"adaptive"         ,1,_ADAPTIVE , _INT_PLOT ,T_NUMBER},
      {"algebraic"              ,0, _SYMB, _INT_TYPE, T_TYPE_ID},
      {"alors",0,0,0,T_THEN},
      {"args",1,0,0,T_ARGS},
      //{"axes"         ,1,_AXES , _INT_PLOT ,T_NUMBER},
      //{"bareiss"         ,1, _BAREISS, _INT_SOLVER,T_NUMBER},
      {"base"         ,1,_BASE , _INT_MAPLECONVERSION ,T_NUMBER},
      {"begin",0,0,0,T_BLOC_BEGIN},
      {"bisection_solver"         ,1, _BISECTION_SOLVER, _INT_SOLVER,T_NUMBER},
      {"black"         ,1, _BLACK, _INT_COLOR ,T_NUMBER},
      //{"blanc"         ,1, _WHITE, _INT_COLOR ,T_NUMBER},
      //{"bleu"         ,1, _BLUE, _INT_COLOR ,T_NUMBER},
      {"blue"         ,1, _BLUE, _INT_COLOR ,T_NUMBER},
      {"brent_solver"         ,1, _BRENT_SOLVER, _INT_SOLVER,T_NUMBER},
      {"by",1,0,0,T_BY},
      {"case",0,0,0,T_CASE},
      {"catch",0,0,0,T_CATCH},
      {"confrac"         ,1,_CONFRAC , _INT_MAPLECONVERSION ,T_NUMBER},
      {"continue",0,0,0,T_CONTINUE},
      {"cyan"         ,1, _CYAN, _INT_COLOR ,T_NUMBER},
      {"de",0,0,0,T_FROM},
      {"default",1,0,0,T_DEFAULT},
      {"dnewton_solver"         ,1, _DNEWTON_SOLVER, _INT_SOLVER,T_NUMBER},
      {"do",0,2,0,T_DO},
      {"double"               ,0, _DOUBLE_, _INT_TYPE, T_TYPE_ID},
      {"downto",0,-1,0,T_TO},
      {"elif",0,0,0,T_ELIF},
      {"else",0,0,0,T_ELSE},
      {"end",0,0,0,T_BLOC_END},
      {"end_case",0,0,0,T_ENDCASE},
      {"end_do",0,2,0,T_BLOC_END},
      {"end_for",0,2,0,T_BLOC_END},
      {"end_if",0,4,0,T_BLOC_END},
      {"end_proc",0,3,0,T_BLOC_END},
      {"end_while",0,2,0,T_BLOC_END},
      {"endfunc",0,3,0,T_BLOC_END},
      {"esac",0,0,0,T_ENDCASE},
      {"expln"         ,1,_EXPLN , _INT_MAPLECONVERSION ,T_NUMBER},
      {"expression"         ,0, _SYMBOL, _INT_TYPE ,T_TYPE_ID},
      //{"faddeev"         ,1, _FADEEV, _INT_SOLVER,T_NUMBER},
      //{"fadeev"         ,1, _FADEEV, _INT_SOLVER,T_NUMBER},
      {"faire",0,2,0,T_DO},
      {"false",1,0,_INT_BOOLEAN,T_NUMBER},
      {"falsepos_solver"         ,1, _FALSEPOS_SOLVER, _INT_SOLVER,T_NUMBER},
      {"ffaire",0,2,0,T_BLOC_END},
      {"ffonction",0,3,0,T_BLOC_END},
      {"ffunction",0,3,0,T_BLOC_END},
      {"fi",0,4,0,T_BLOC_END},
      {"filled"         ,1, _FILL_POLYGON, _INT_COLOR ,T_NUMBER},
      {"float"                ,0, _DOUBLE_, _INT_TYPE, T_TYPE_ID},
      {"fonction",0,0,0,T_PROC},
      {"for",0,0,0,T_FOR},
      {"fpour",0,2,0,T_BLOC_END},
      {"from",0,0,0,T_FROM},
      {"fsi",0,4,0,T_BLOC_END},
      {"ftantque",0,8,0,T_BLOC_END},
      {"fullparfrac"         ,1,_FULLPARFRAC , _INT_MAPLECONVERSION ,T_NUMBER},
      {"func"                ,0, _FUNC, _INT_TYPE, T_TYPE_ID},
      {"function",0,0,0,T_PROC},
      //{"gauss15"         ,1, _GAUSS15, _INT_SOLVER,T_NUMBER},
      //{"gl_x"       ,1,_GL_X , _INT_PLOT ,T_NUMBER},
      //{"gl_y"       ,1,_GL_Y , _INT_PLOT ,T_NUMBER},
      {"global",0,1,0,T_LOCAL},
      //{"golub_reinsch_decomp"         ,1, _GOLUB_REINSCH_DECOMP, _INT_SOLVER,T_NUMBER},
      //{"golub_reinsch_mod_decomp"         ,1, _GOLUB_REINSCH_MOD_DECOMP, _INT_SOLVER,T_NUMBER},
      {"green"         ,1, _GREEN, _INT_COLOR ,T_NUMBER},
      //{"hybrid_solver"         ,1, _HYBRID_SOLVER, _INT_SOLVER,T_NUMBER},
      //{"hybridj_solver"         ,1, _HYBRIDJ_SOLVER, _INT_SOLVER,T_NUMBER},
      //{"hybrids_solver"         ,1, _HYBRIDS_SOLVER, _INT_SOLVER,T_NUMBER},
      //{"hybridsj_solver"         ,1, _HYBRIDSJ_SOLVER, _INT_SOLVER,T_NUMBER},
      {"identifier"            ,0, _IDNT, _INT_TYPE, T_TYPE_ID},
      {"if",0,0,0,T_IF},
      {"in",0,0,0,T_IN},
      {"integer"               ,0, _ZINT, _INT_TYPE, T_TYPE_ID},
      {"intersect",0,0,0,T_INTERSECT},
      //{"jacobi_decomp"         ,1, _JACOBI_DECOMP, _INT_SOLVER,T_NUMBER},
      //{"jaune"         ,1, _YELLOW, _INT_COLOR ,T_NUMBER},
      {"jusque",0,1,0,T_TO},
      {"keep_pivot"         ,1, _KEEP_PIVOT, _INT_SOLVER,T_NUMBER},
      //{"left_rectangle"         ,1, _RECTANGLE_GAUCHE, _INT_SOLVER,T_NUMBER},
      {"line_width_2"         ,1, _LINE_WIDTH_2 , _INT_COLOR ,T_NUMBER},
      {"line_width_3"         ,1, _LINE_WIDTH_3 , _INT_COLOR ,T_NUMBER},
      {"line_width_4"         ,1, _LINE_WIDTH_4 , _INT_COLOR ,T_NUMBER},
      //{"line_width_5"         ,1, _LINE_WIDTH_5 , _INT_COLOR ,T_NUMBER},
      //{"line_width_6"         ,1, _LINE_WIDTH_6 , _INT_COLOR ,T_NUMBER},
      //{"line_width_7"         ,1, _LINE_WIDTH_7 , _INT_COLOR ,T_NUMBER},
      //{"line_width_8"         ,1, _LINE_WIDTH_8 , _INT_COLOR ,T_NUMBER},
      {"local",0,0,0,T_LOCAL},
      {"magenta"         ,1, _MAGENTA, _INT_COLOR ,T_NUMBER},
      {"middle_point"         ,1, _POINT_MILIEU, _INT_SOLVER,T_NUMBER},
      //{"minor_det"         ,1, _MINOR_DET, _INT_SOLVER,T_NUMBER},
      {"minus",0,0,0,T_MINUS},
      //{"modular_check"         ,1,_MODULAR_CHECK , _INT_GROEBNER ,T_NUMBER},
      {"negint"               ,0, _NEGINT, _INT_MAPLECONVERSION, T_TYPE_ID},
      {"newton_solver"         ,1, _NEWTON_SOLVER, _INT_SOLVER,T_NUMBER},
      //{"newtonj_solver"         ,1, _NEWTONJ_SOLVER, _INT_SOLVER,T_NUMBER},
      {"next",0,0,0,T_CONTINUE},
      //{"noir"         ,1, _BLACK, _INT_COLOR ,T_NUMBER},
      {"nonnegint"               ,0, _NONNEGINT, _INT_MAPLECONVERSION, T_TYPE_ID},
      {"nonposint"               ,0, _NONPOSINT, _INT_MAPLECONVERSION, T_TYPE_ID},
      //{"nstep"         ,1, _NSTEP , _INT_PLOT ,T_NUMBER},
      {"od",0,9,0,T_BLOC_END},
      {"of",0,0,0,T_OF},
      {"otherwise",0,0,0,T_DEFAULT},
      {"parfrac"         ,1,_PARFRAC , _INT_MAPLECONVERSION ,T_NUMBER},
      {"pas",0,0,0,T_BY},
      //{"plex"         ,1,_PLEX_ORDER , _INT_GROEBNER ,T_NUMBER},
      {"plus_point"         ,1, _POINT_PLUS , _INT_COLOR ,T_NUMBER},
      {"point_milieu"         ,1, _POINT_MILIEU, _INT_SOLVER,T_NUMBER},
      {"polynom"         ,0,_POLY1__VECT , _INT_MAPLECONVERSION ,T_TYPE_ID},
      {"posint"               ,0, _POSINT, _INT_MAPLECONVERSION, T_TYPE_ID},
      {"pour",0,0,0,T_FOR},
      {"proc",0,0,0,T_PROC},
      //{"quadrant1"         ,1, _QUADRANT1 , _INT_COLOR ,T_NUMBER},
      //{"quadrant2"         ,1, _QUADRANT2 , _INT_COLOR ,T_NUMBER},
      //{"quadrant3"         ,1, _QUADRANT3 , _INT_COLOR ,T_NUMBER},
      //{"quadrant4"         ,1, _QUADRANT4 , _INT_COLOR ,T_NUMBER},
      {"rational"              ,0, _FRAC, _INT_TYPE, T_TYPE_ID},
      //{"rational_det"         ,1, _RATIONAL_DET, _INT_SOLVER,T_NUMBER},
      {"rectangle_droit"         ,1, _RECTANGLE_DROIT, _INT_SOLVER,T_NUMBER},
      {"rectangle_gauche"         ,1, _RECTANGLE_GAUCHE, _INT_SOLVER,T_NUMBER},
      {"red"         ,1, _RED, _INT_COLOR ,T_NUMBER},
      //{"rempli"         ,1, _FILL_POLYGON , _INT_COLOR ,T_NUMBER},
      //{"resolution"         ,1,_RESOLUTION , _INT_PLOT ,T_NUMBER},
      {"retourne",0,0,0,T_RETURN},
      {"return",0,0,0,T_RETURN},
      //{"revlex"         ,1,_REVLEX_ORDER , _INT_GROEBNER ,T_NUMBER},
      //{"rhombus_point"         ,1, _POINT_LOSANGE , _INT_COLOR ,T_NUMBER},
      //{"right_rectangle"         ,1, _RECTANGLE_DROIT, _INT_SOLVER,T_NUMBER},
      {"rombergm"         ,1, _ROMBERGM, _INT_SOLVER,T_NUMBER},
      {"rombergt"         ,1, _ROMBERGT, _INT_SOLVER,T_NUMBER},
      //{"rouge"         ,1, _RED, _INT_COLOR ,T_NUMBER},
      //{"rur"         ,1,_RUR_REVLEX , _INT_GROEBNER ,T_NUMBER},
      {"secant_solver"         ,1, _SECANT_SOLVER, _INT_SOLVER,T_NUMBER},
      {"set"         ,0,_SET__VECT , _INT_MAPLECONVERSION ,T_TYPE_ID},
      {"si",0,0,0,T_IF},
      {"simpson"         ,1, _SIMPSON, _INT_SOLVER,T_NUMBER},
      {"sinon",0,0,0,T_ELSE},
      //{"square_point"         ,1, _POINT_CARRE  , _INT_COLOR ,T_NUMBER},
      //{"star_point"         ,1, _POINT_ETOILE , _INT_COLOR ,T_NUMBER},
      //{"steffenson_solver"         ,1, _STEFFENSON_SOLVER, _INT_SOLVER,T_NUMBER},
      {"step",0,0,0,T_BY},
      {"switch",0,0,0,T_SWITCH},
      {"tantque",0,0,0,T_WHILE},
      //{"tdeg"         ,1,_TDEG_ORDER , _INT_GROEBNER ,T_NUMBER},
      {"then",0,0,0,T_THEN},
      {"to",0,1,0,T_TO},
      {"trapeze"         ,1, _TRAPEZE, _INT_SOLVER,T_NUMBER},
      {"trapezoid"         ,1, _TRAPEZE, _INT_SOLVER,T_NUMBER},
      //{"triangle_point"         ,1, _POINT_TRIANGLE , _INT_COLOR ,T_NUMBER},
      {"trig"         ,1,_TRIG , _INT_MAPLECONVERSION ,T_NUMBER},
      {"true",1,1,_INT_BOOLEAN,T_NUMBER},
      {"try",0,0,0,T_TRY},
      {"try_catch",0,0,0,T_TRY_CATCH},
      {"tstep"         ,1, _TSTEP , _INT_PLOT ,T_NUMBER},
      {"unfactored"         ,1, _UNFACTORED, _INT_SOLVER,T_NUMBER},
      {"union",0,0,0,T_UNION},
      {"until",0,0,0,T_UNTIL},
      //{"ustep"         ,1, _USTEP , _INT_PLOT ,T_NUMBER},
      {"var",0,0,0,T_LOCAL},
      //{"vert"         ,1, _GREEN, _INT_COLOR ,T_NUMBER},
      //{"vstep"         ,1, _VSTEP , _INT_PLOT ,T_NUMBER},
      {"while",0,0,0,T_WHILE},
      {"white"         ,1, _WHITE, _INT_COLOR ,T_NUMBER},
      {"xstep"         ,1, _XSTEP , _INT_PLOT ,T_NUMBER},
      {"yellow"         ,1, _YELLOW, _INT_COLOR ,T_NUMBER},
      //{"ystep"         ,1, _YSTEP , _INT_PLOT ,T_NUMBER},
      //{"zstep"         ,1, _ZSTEP , _INT_PLOT ,T_NUMBER}

