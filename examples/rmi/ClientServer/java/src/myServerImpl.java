package dds.rmi.example;

public class myServerImpl extends DDS_RMI.ClientServer.myServerInterface
{
    org.opensplice.DDS_RMI.CRuntime runtime;

  public myServerImpl (org.opensplice.DDS_RMI.CRuntime _runtime) {
      this.runtime = _runtime;
  }

  public void set_temperature(float temp)
  {
    org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "=== set_temperature handled, temp=%f\n", temp) ;
  }

  public void set_humidity(float hum) {
      org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "=== set_humidity handled, hum=%f\n", hum) ;
 }

  public void set_fan_level(short level) {
       org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "=== set_humidity handled, level=%d\n", level) ;
}

  public void test_sequence_string (
      ClientServer.string_seqHolder test) {
	      org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "=== test_sequence_string handled\n") ;
 }

    public  void test_inout_string (
      String in_string,
      DDS.StringHolder inout_string,
      DDS.StringHolder out_string) {
	      org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "=== test_inout_string handled\n") ;
 }

  public void test_sequence_long(int[] test){
       org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "=== test_sequence_long handled\n") ;
}
  public void test_sequence_TestStruct(ClientServer.TestStruct[]test){
       org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "=== test_sequence_TestStruct handled\n") ;
}

  public void setTopicQoS(DDS.TopicQos qos, int opIndex, int mode)
  {
  }

  public void get_details(DDS.StringHolder infos) {
      org.opensplice.DDS_RMI.Sync_Print.stdOutFormat (
	    "=== get_details handled\n", infos.value) ;
      infos.value = "Server Details" ;
  }

  public short start () { return 0 ; }
  public short stop ()
  {
      // Stopping the service
      org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("=== Service shutdown\n") ;
      runtime.shutdown(false);
      return 0;
  }
  public boolean raise_temp_to(float temp,
    org.opensplice.DDS_RMI.IntHolder hum, org.opensplice.DDS_RMI.ShortHolder level)
  {
    if (80 == hum.value)
    {
      try
      {
        synchronized(hum)
        {
          hum.wait (1000);
        }
      }
      catch (InterruptedException e)
      {
        e.printStackTrace();
      }

      org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ("=== async_raise_temp_to\n") ;
      return true;
    }
    hum.value = 70 ;
    level.value = 7 ;
    org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "=== raise_temp_to handled\n") ;
    return true ;
  }

  @Override
  public void resume()
  {

  }

  @Override
  public void suspend()
  {

  }

}
