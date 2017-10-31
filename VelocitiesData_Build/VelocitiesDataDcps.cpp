//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: VelocitiesDataDcps.cpp
//  Source: VelocitiesData_Build/VelocitiesDataDcps.idl
//  Generated: Tue Oct 31 12:03:13 2017
//  OpenSplice 6.8.2
//  
//******************************************************************

#include "VelocitiesDataDcps.h"

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUFLSeq < VelocitiesData::Velocities, struct VelocitiesSeq_uniq_>;
#endif

const char * VelocitiesData::VelocitiesTypeSupportInterface::_local_id = "IDL:VelocitiesData/VelocitiesTypeSupportInterface:1.0";

VelocitiesData::VelocitiesTypeSupportInterface_ptr VelocitiesData::VelocitiesTypeSupportInterface::_duplicate (VelocitiesData::VelocitiesTypeSupportInterface_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean VelocitiesData::VelocitiesTypeSupportInterface::_local_is_a (const char * _id)
{
   if (strcmp (_id, VelocitiesData::VelocitiesTypeSupportInterface::_local_id) == 0)
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

VelocitiesData::VelocitiesTypeSupportInterface_ptr VelocitiesData::VelocitiesTypeSupportInterface::_narrow (DDS::Object_ptr p)
{
   VelocitiesData::VelocitiesTypeSupportInterface_ptr result = NULL;
   if (p && p->_is_a (VelocitiesData::VelocitiesTypeSupportInterface::_local_id))
   {
      result = dynamic_cast < VelocitiesData::VelocitiesTypeSupportInterface_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

VelocitiesData::VelocitiesTypeSupportInterface_ptr VelocitiesData::VelocitiesTypeSupportInterface::_unchecked_narrow (DDS::Object_ptr p)
{
   VelocitiesData::VelocitiesTypeSupportInterface_ptr result;
   result = dynamic_cast < VelocitiesData::VelocitiesTypeSupportInterface_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * VelocitiesData::VelocitiesDataWriter::_local_id = "IDL:VelocitiesData/VelocitiesDataWriter:1.0";

VelocitiesData::VelocitiesDataWriter_ptr VelocitiesData::VelocitiesDataWriter::_duplicate (VelocitiesData::VelocitiesDataWriter_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean VelocitiesData::VelocitiesDataWriter::_local_is_a (const char * _id)
{
   if (strcmp (_id, VelocitiesData::VelocitiesDataWriter::_local_id) == 0)
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

VelocitiesData::VelocitiesDataWriter_ptr VelocitiesData::VelocitiesDataWriter::_narrow (DDS::Object_ptr p)
{
   VelocitiesData::VelocitiesDataWriter_ptr result = NULL;
   if (p && p->_is_a (VelocitiesData::VelocitiesDataWriter::_local_id))
   {
      result = dynamic_cast < VelocitiesData::VelocitiesDataWriter_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

VelocitiesData::VelocitiesDataWriter_ptr VelocitiesData::VelocitiesDataWriter::_unchecked_narrow (DDS::Object_ptr p)
{
   VelocitiesData::VelocitiesDataWriter_ptr result;
   result = dynamic_cast < VelocitiesData::VelocitiesDataWriter_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * VelocitiesData::VelocitiesDataReader::_local_id = "IDL:VelocitiesData/VelocitiesDataReader:1.0";

VelocitiesData::VelocitiesDataReader_ptr VelocitiesData::VelocitiesDataReader::_duplicate (VelocitiesData::VelocitiesDataReader_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean VelocitiesData::VelocitiesDataReader::_local_is_a (const char * _id)
{
   if (strcmp (_id, VelocitiesData::VelocitiesDataReader::_local_id) == 0)
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

VelocitiesData::VelocitiesDataReader_ptr VelocitiesData::VelocitiesDataReader::_narrow (DDS::Object_ptr p)
{
   VelocitiesData::VelocitiesDataReader_ptr result = NULL;
   if (p && p->_is_a (VelocitiesData::VelocitiesDataReader::_local_id))
   {
      result = dynamic_cast < VelocitiesData::VelocitiesDataReader_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

VelocitiesData::VelocitiesDataReader_ptr VelocitiesData::VelocitiesDataReader::_unchecked_narrow (DDS::Object_ptr p)
{
   VelocitiesData::VelocitiesDataReader_ptr result;
   result = dynamic_cast < VelocitiesData::VelocitiesDataReader_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * VelocitiesData::VelocitiesDataReaderView::_local_id = "IDL:VelocitiesData/VelocitiesDataReaderView:1.0";

VelocitiesData::VelocitiesDataReaderView_ptr VelocitiesData::VelocitiesDataReaderView::_duplicate (VelocitiesData::VelocitiesDataReaderView_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean VelocitiesData::VelocitiesDataReaderView::_local_is_a (const char * _id)
{
   if (strcmp (_id, VelocitiesData::VelocitiesDataReaderView::_local_id) == 0)
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

VelocitiesData::VelocitiesDataReaderView_ptr VelocitiesData::VelocitiesDataReaderView::_narrow (DDS::Object_ptr p)
{
   VelocitiesData::VelocitiesDataReaderView_ptr result = NULL;
   if (p && p->_is_a (VelocitiesData::VelocitiesDataReaderView::_local_id))
   {
      result = dynamic_cast < VelocitiesData::VelocitiesDataReaderView_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

VelocitiesData::VelocitiesDataReaderView_ptr VelocitiesData::VelocitiesDataReaderView::_unchecked_narrow (DDS::Object_ptr p)
{
   VelocitiesData::VelocitiesDataReaderView_ptr result;
   result = dynamic_cast < VelocitiesData::VelocitiesDataReaderView_ptr> (p);
   if (result) result->m_count++;
   return result;
}


