{% include "source_file_header.txt" %}

#include "oyranos_object_internal.h"

#include "{{ class.name }}.h"
#include "{{ class.privName }}.h"

#include "oyObject_s.h"

/** @brief oyName_s copy
 *
 *  @version Oyranos: 0.1.10
 *  @since   2008/12/22 (Oyranos: 0.1.10)
 *  @date    2008/12/22
 */
int          oyName_copy_            ( oyName_s          * dest,
                                       oyName_s          * src,
                                       oyObject_s          object )
{
  int error = 0;
  oyName_s * s = dest;
  oyAlloc_f   allocateFunc   = oyAllocateFunc_;
  oyDeAlloc_f deallocateFunc = oyDeAllocateFunc_;

  if(!src || !dest)
    return 0;

  if(object)
  {
    allocateFunc = object->allocateFunc_;
    deallocateFunc = object->deallocateFunc_;
  }

  if(src->name)
    s = oyName_set_ ( s, src->name, oyNAME_NAME, allocateFunc, deallocateFunc );
  if(src->nick)
    s = oyName_set_ ( s, src->nick, oyNAME_NICK, allocateFunc, deallocateFunc );
  if(src->description)
    s = oyName_set_ ( s, src->description, oyNAME_DESCRIPTION, allocateFunc, deallocateFunc );

  if(!s)
    s = oyName_new(0);

  if(error <= 0)
    error = !memcpy( s->lang, src->lang, 8 );

  return error;
}

/**
 *  @internal
 *  @brief oyName_s deallocation
 *
 *  @since Oyranos: version 0.1.8
 *  @date  october 2007 (API 0.1.8)
 */
int          oyName_release_         ( oyName_s         ** obj,
                                       oyDeAlloc_f         deallocateFunc )
{
  /* ---- start of common object destructor ----- */
  oyName_s * s = 0;

  if(!obj || !*obj)
    return 0;

  s = *obj;

  if( s->type != oyOBJECT_NAME_S)
  {
    WARNc_S(("Attempt to release a non oyName_s object."))
    return 1;
  }
  /* ---- end of common object destructor ------- */

  *obj = 0;

  if(!deallocateFunc)
    return 0;

  oyName_releaseMembers( s, deallocateFunc );

  deallocateFunc( s );

  return 0;
}

/**
 *  @internal
 *  @brief naming plus automatic allocation
 *
 *  @param[in]    obj            the oyName_s struct
 *  @param[in]    text           the name should fit into usual labels
 *  @param[in]    type           the kind of name
 *  @param[in]    allocateFunc   memory management (defaults to oyAllocateFunc_)
 *  @param[in]    deallocateFunc optional memory management 
 *
 *  @since Oyranos: version 0.1.8
 *  @date  november 2007 (API 0.1.8)
 */
oyName_s *   oyName_set_             ( oyName_s          * obj,
                                       const char        * text,
                                       oyNAME_e            type,
                                       oyAlloc_f           allocateFunc,
                                       oyDeAlloc_f         deallocateFunc )
{
  int error = 0;
  oyName_s * s = obj;

  if(obj && obj->type != oyOBJECT_NAME_S)
  {
    WARNc_S(("Attempt to edit a non oyName_s object."))
    return 0;
  }

  if(!s)
    s = oyName_new(0);

  if(!s) return s;

  s->type = oyOBJECT_NAME_S;

  {
#define oySetString_m(n_type)\
    if(error <= 0) { \
      if(s->n_type && deallocateFunc) \
        deallocateFunc( s->n_type ); \
      s->n_type = oyStringCopy_( text, allocateFunc ); \
      if( !s->n_type ) error = 1; \
    } 
    switch (type) {
    case oyNAME_NICK:
         oySetString_m(nick) break;
    case oyNAME_NAME:
         oySetString_m(name) break;
    case oyNAME_DESCRIPTION:
         oySetString_m(description) break;
    default: break;
    }
#undef oySetString_
  }

  return s;
}

/**
 *  @internal
 *  Function oyName_get_
 *  @brief   get name
 *
 *  @param[in,out] obj                 name object
 *  @param         type                type of name
 *
 *  @version Oyranos: 0.1.8
 *  @since   2008/07/18 (Oyranos: 0.1.8)
 *  @date    2008/07/18
 */
const char * oyName_get_             ( const oyName_s    * obj,
                                       oyNAME_e            type )
{
  const char * text = 0;
  const oyName_s * name = obj;
  if(!obj)
    return 0;

  switch(type)
  {
    case oyNAME_NICK:
         text = name->nick; break;
    case oyNAME_DESCRIPTION:
         text = name->description; break;
    case oyNAME_NAME:
    default:
         text = name->name; break;
  }

  return text;
}

/** Function oyName_releaseMembers
 *  @memberof oyName_s
 *  @brief   release only members
 *
 *  Useful to release the member strings but not the struct itself, which can
 *  in this case be static. Deallocation uses oyDeAllocateFunc_().
 *
 *  @version Oyranos: 0.1.9
 *  @since   2008/11/13 (Oyranos: 0.1.9)
 *  @date    2008/11/13
 */
int          oyName_releaseMembers   ( oyName_s          * obj,
                                       oyDeAlloc_f         deallocateFunc )
{
  int error = 0;
  oyName_s * s = 0;

  if(!obj)
    return 0;

  if(!deallocateFunc)
    deallocateFunc = oyDeAllocateFunc_;

  s = obj;

  if(s->nick)
    deallocateFunc(s->nick); s->nick = 0;

  if(s->name)
    deallocateFunc(s->name); s->name = 0;

  if(s->description)
    deallocateFunc(s->description); s->description = 0;

  return error;
}
