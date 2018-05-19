# Functions
FUNCTION (GET_VARS_STARTING_WITH _prefix _varResult)
    GET_CMAKE_PROPERTY(_vars VARIABLES)
    STRING(REGEX MATCHALL "(^|;)${_prefix}[A-Za-z0-9_]*" _matchedVars "${_vars}")
    SET(${_varResult} ${_matchedVars} PARENT_SCOPE)
ENDFUNCTION()

FUNCTION(UNSET_VAR _var)
  UNSET(${_var} CACHE)
  UNSET(${_var})
ENDFUNCTION()

FUNCTION(UNSET_VARS_STARTING_WITH _prefix)
  GET_VARS_STARTING_WITH(${_prefix} _vars)
  FOREACH(_var IN LISTS _vars)
    UNSET_VAR(${_var})
  ENDFOREACH()
ENDFUNCTION()
