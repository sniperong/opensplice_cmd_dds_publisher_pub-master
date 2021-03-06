//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: ContentFilteredTopicDataDcps.cpp
//  Source: ContentFilteredTopicDataDcps.idl
//  Generated: Mon Oct 23 17:11:30 2017
//  OpenSplice 6.8.2
//  
//******************************************************************

#include "ContentFilteredTopicDataDcps.h"

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUVLSeq < StockMarket::Stock, struct StockSeq_uniq_>;
#endif

const char * StockMarket::StockTypeSupportInterface::_local_id = "IDL:StockMarket/StockTypeSupportInterface:1.0";

StockMarket::StockTypeSupportInterface_ptr StockMarket::StockTypeSupportInterface::_duplicate (StockMarket::StockTypeSupportInterface_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean StockMarket::StockTypeSupportInterface::_local_is_a (const char * _id)
{
   if (strcmp (_id, StockMarket::StockTypeSupportInterface::_local_id) == 0)
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

StockMarket::StockTypeSupportInterface_ptr StockMarket::StockTypeSupportInterface::_narrow (DDS::Object_ptr p)
{
   StockMarket::StockTypeSupportInterface_ptr result = NULL;
   if (p && p->_is_a (StockMarket::StockTypeSupportInterface::_local_id))
   {
      result = dynamic_cast < StockMarket::StockTypeSupportInterface_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

StockMarket::StockTypeSupportInterface_ptr StockMarket::StockTypeSupportInterface::_unchecked_narrow (DDS::Object_ptr p)
{
   StockMarket::StockTypeSupportInterface_ptr result;
   result = dynamic_cast < StockMarket::StockTypeSupportInterface_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * StockMarket::StockDataWriter::_local_id = "IDL:StockMarket/StockDataWriter:1.0";

StockMarket::StockDataWriter_ptr StockMarket::StockDataWriter::_duplicate (StockMarket::StockDataWriter_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean StockMarket::StockDataWriter::_local_is_a (const char * _id)
{
   if (strcmp (_id, StockMarket::StockDataWriter::_local_id) == 0)
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

StockMarket::StockDataWriter_ptr StockMarket::StockDataWriter::_narrow (DDS::Object_ptr p)
{
   StockMarket::StockDataWriter_ptr result = NULL;
   if (p && p->_is_a (StockMarket::StockDataWriter::_local_id))
   {
      result = dynamic_cast < StockMarket::StockDataWriter_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

StockMarket::StockDataWriter_ptr StockMarket::StockDataWriter::_unchecked_narrow (DDS::Object_ptr p)
{
   StockMarket::StockDataWriter_ptr result;
   result = dynamic_cast < StockMarket::StockDataWriter_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * StockMarket::StockDataReader::_local_id = "IDL:StockMarket/StockDataReader:1.0";

StockMarket::StockDataReader_ptr StockMarket::StockDataReader::_duplicate (StockMarket::StockDataReader_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean StockMarket::StockDataReader::_local_is_a (const char * _id)
{
   if (strcmp (_id, StockMarket::StockDataReader::_local_id) == 0)
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

StockMarket::StockDataReader_ptr StockMarket::StockDataReader::_narrow (DDS::Object_ptr p)
{
   StockMarket::StockDataReader_ptr result = NULL;
   if (p && p->_is_a (StockMarket::StockDataReader::_local_id))
   {
      result = dynamic_cast < StockMarket::StockDataReader_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

StockMarket::StockDataReader_ptr StockMarket::StockDataReader::_unchecked_narrow (DDS::Object_ptr p)
{
   StockMarket::StockDataReader_ptr result;
   result = dynamic_cast < StockMarket::StockDataReader_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * StockMarket::StockDataReaderView::_local_id = "IDL:StockMarket/StockDataReaderView:1.0";

StockMarket::StockDataReaderView_ptr StockMarket::StockDataReaderView::_duplicate (StockMarket::StockDataReaderView_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean StockMarket::StockDataReaderView::_local_is_a (const char * _id)
{
   if (strcmp (_id, StockMarket::StockDataReaderView::_local_id) == 0)
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

StockMarket::StockDataReaderView_ptr StockMarket::StockDataReaderView::_narrow (DDS::Object_ptr p)
{
   StockMarket::StockDataReaderView_ptr result = NULL;
   if (p && p->_is_a (StockMarket::StockDataReaderView::_local_id))
   {
      result = dynamic_cast < StockMarket::StockDataReaderView_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

StockMarket::StockDataReaderView_ptr StockMarket::StockDataReaderView::_unchecked_narrow (DDS::Object_ptr p)
{
   StockMarket::StockDataReaderView_ptr result;
   result = dynamic_cast < StockMarket::StockDataReaderView_ptr> (p);
   if (result) result->m_count++;
   return result;
}



