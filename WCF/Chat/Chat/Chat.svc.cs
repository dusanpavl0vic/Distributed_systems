﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace Chat
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.PerSession, ConcurrencyMode=ConcurrencyMode.Reentrant)]
    public class Chat : IChat
    {
        static Dictionary<string, IChatCallback> korisnici = new Dictionary<string, IChatCallback>();
        static List<Message> messages = new List<Message>();

        string rname;

        public IList<Message> MsgHistory(DateTime from, DateTime to)
        {
            return messages.Where(m => 
                (m.To == rname || m.To == "SVI")
                && m.Timestamp >= from && m.Timestamp <= to)
                .ToList();
        }

        public void register(string name)
        {
            rname = name;
            if (!korisnici.ContainsKey(name))
                korisnici.Add(name, null);

            korisnici[name] = OperationContext.Current.GetCallbackChannel<IChatCallback>();
        }

        public void Send(Message m)
        {
            m.Timestamp = DateTime.Now;
            m.From = rname;
            messages.Add(m);

            if(m.To.Equals("SVI"))
            {
                foreach(var k in korisnici.Keys)
                    if(k != rname)
                        korisnici[k].notify(m);
            }
            else
                if(korisnici.ContainsKey(m.To))
                    korisnici[m.To].notify(m);
        }
    }
}
