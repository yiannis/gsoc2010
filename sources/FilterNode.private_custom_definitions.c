/** Function    oyFilterNode_Release__Members
 *  @memberof   oyFilterNode_s
 *  @brief      Custom FilterNode destructor
 *  @internal
 *
 *  This function will free up all memmory allocated by the
 *  input object. First all object members witch have their
 *  own release method are deallocated. Then the deallocateFunc_
 *  of the oy_ object is used to release the rest of the members
 *  that were allocated with oy_->allocateFunc_.
 *
 *  @param[in]  filternode  the FilterNode object
 *
 *  @version Oyranos: x.x.x
 *  @since   YYYY/MM/DD (Oyranos: x.x.x)
 *  @date    YYYY/MM/DD
 */
void oyFilterNode_Release__Members( oyFilterNode_s_ * filternode )
{
  /* Deallocate members here
   * E.g: oyXXX_Release( &filternode->member );
   */

  if(filternode->oy_->deallocateFunc_)
  {
    oyDeAlloc_f deallocateFunc = filternode->oy_->deallocateFunc_;

    /* Deallocate members of basic type here
     * E.g.: deallocateFunc( filternode->member );
     */
  }
}

/** Function    oyFilterNode_Init__Members
 *  @memberof   oyFilterNode_s
 *  @brief      Custom FilterNode constructor 
 *  @internal
 *
 *  This function will allocate all memmory for the input object.
 *  For the basic member types this is done using the allocateFunc_
 *  of the attatced (oyObject_s)oy_ object.
 *
 *  @param[in]  filternode  the FilterNode object
 *
 *  @version Oyranos: x.x.x
 *  @since   YYYY/MM/DD (Oyranos: x.x.x)
 *  @date    YYYY/MM/DD
 */
int oyFilterNode_Init__Members( oyFilterNode_s_ * filternode )
{
  return 0;
}

/** Function    oyFilterNode_Copy__Members
 *  @memberof   oyFilterNode_s
 *  @brief      Custom FilterNode copy constructor
 *  @internal
 *
 *  This function makes a copy of all values from the input
 *  to the output object. The destination object and all of its
 *  members should already be allocated.
 *
 *  @param[in]   src  the oyFilterNode_s_ input object
 *  @param[out]  dst  the output oyFilterNode_s_ object
 *
 *  @version Oyranos: x.x.x
 *  @since   YYYY/MM/DD (Oyranos: x.x.x)
 *  @date    YYYY/MM/DD
 */
int oyFilterNode_Copy__Members( oyFilterNode_s_ * dst, oyFilterNode_s_ * src)
{
  int error = 0;
  oyAlloc_f allocateFunc_ = 0;
  oyDeAlloc_f deallocateFunc_ = 0;

  if(!dst || !src)
    return 1;

  allocateFunc_ = dst->oy_->allocateFunc_;
  deallocateFunc_ = dst->oy_->deallocateFunc_;

  /* Copy each value of src to dst here */

  return error;
}