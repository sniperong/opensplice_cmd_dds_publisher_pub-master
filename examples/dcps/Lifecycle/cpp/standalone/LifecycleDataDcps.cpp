//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: LifecycleDataDcps.cpp
//  Source: LifecycleDataDcps.idl
//  Generated: Mon Oct 23 17:12:13 2017
//  OpenSplice 6.8.2
//  
//******************************************************************

#include "LifecycleDataDcps.h"

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUVLSeq < LifecycleData::Msg, struct MsgSeq_uniq_>;
#endif

const char * LifecycleData::MsgTypeSupportInterface::_local_id = "IDL:LifecycleData/MsgTypeSupportInterface:1.0";

LifecycleData::MsgTypeSupportInterface_ptr LifecycleData::MsgTypeSupportInterface::_duplicate (LifecycleData::MsgTypeSupportInterface_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean LifecycleData::MsgTypeSupportInterface::_local_is_a (const char * _id)
{
   if (strcmp (_id, LifecycleData::MsgTypeSupportInterface::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::TypeSupport NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

LifecycleData::MsgTypeSupportInterface_ptr LifecycleData::MsgTypeSupportInterface::_narrow (DDS::Object_ptr p)
{
   LifecycleData::MsgTypeSupportInterface_ptr result = NULL;
   if (p && p->_is_a (LifecycleData::MsgTypeSupportInterface::_local_id))
   {
      result = dynamic_cast < LifecycleData::MsgTypeSupportInterface_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

LifecycleData::MsgTypeSupportInterface_ptr LifecycleData::MsgTypeSupportInterface::_unchecked_narrow (DDS::Object_ptr p)
{
   LifecycleData::MsgTypeSupportInterface_ptr result;
   result = dynamic_cast < LifecycleData::MsgTypeSupportInterface_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * LifecycleData::MsgDataWriter::_local_id = "IDL:LifecycleData/MsgDataWriter:1.0";

LifecycleData::MsgDataWriter_ptr LifecycleData::MsgDataWriter::_duplicate (LifecycleData::MsgDataWriter_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean LifecycleData::MsgDataWriter::_local_is_a (const char * _id)
{
   if (strcmp (_id, LifecycleData::MsgDataWriter::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataWriter NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

LifecycleData::MsgDataWriter_ptr LifecycleData::MsgDataWriter::_narrow (DDS::Object_ptr p)
{
   LifecycleData::MsgDataWriter_ptr result = NULL;
   if (p && p->_is_a (LifecycleData::MsgDataWriter::_local_id))
   {
      result = dynamic_cast < LifecycleData::MsgDataWriter_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

LifecycleData::MsgDataWriter_ptr LifecycleData::MsgDataWriter::_unchecked_narrow (DDS::Object_ptr p)
{
   LifecycleData::MsgDataWriter_ptr result;
   result = dynamic_cast < LifecycleData::MsgDataWriter_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * LifecycleData::MsgDataReader::_local_id = "IDL:LifecycleData/MsgDataReader:1.0";

LifecycleData::MsgDataReader_ptr LifecycleData::MsgDataReader::_duplicate (LifecycleData::MsgDataReader_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean LifecycleData::MsgDataReader::_local_is_a (const char * _id)
{
   if (strcmp (_id, LifecycleData::MsgDataReader::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataReader NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

LifecycleData::MsgDataReader_ptr LifecycleData::MsgDataReader::_narrow (DDS::Object_ptr p)
{
   LifecycleData::MsgDataReader_ptr result = NULL;
   if (p && p->_is_a (LifecycleData::MsgDataReader::_local_id))
   {
      result = dynamic_cast < LifecycleData::MsgDataReader_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

LifecycleData::MsgDataReader_ptr LifecycleData::MsgDataReader::_unchecked_narrow (DDS::Object_ptr p)
{
   LifecycleData::MsgDataReader_ptr result;
   result = dynamic_cast < LifecycleData::MsgDataReader_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * LifecycleData::MsgDataReaderView::_local_id = "IDL:LifecycleData/MsgDataReaderView:1.0";

LifecycleData::MsgDataReaderView_ptr LifecycleData::MsgDataReaderView::_duplicate (LifecycleData::MsgDataReaderView_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean LifecycleData::MsgDataReaderView::_local_is_a (const char * _id)
{
   if (strcmp (_id, LifecycleData::MsgDataReaderView::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataReaderView NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

LifecycleData::MsgDataReaderView_ptr LifecycleData::MsgDataReaderView::_narrow (DDS::Object_ptr p)
{
   LifecycleData::MsgDataReaderView_ptr result = NULL;
   if (p && p->_is_a (LifecycleData::MsgDataReaderView::_local_id))
   {
      result = dynamic_cast < LifecycleData::MsgDataReaderView_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

LifecycleData::MsgDataReaderView_ptr LifecycleData::MsgDataReaderView::_unchecked_narrow (DDS::Object_ptr p)
{
   LifecycleData::MsgDataReaderView_ptr result;
   result = dynamic_cast < LifecycleData::MsgDataReaderView_ptr> (p);
   if (result) result->m_count++;
   return result;
}



