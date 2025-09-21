using Grpc.Net.Client;
using System.Xml.Linq;

namespace GrpcClient
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            Console.WriteLine("Hello, World!");

            using var channel = GrpcChannel.ForAddress("https://localhost:7030");
            var client = new KorisnikService.KorisnikServiceClient(channel);
            int i = 1;
            pocetak:

            Console.ReadKey();

            var reply = await client.AddKorisnikAsync(new Korisnik
            {
                Id = i,
                Name = "Dusan",
                Adresa = "Neka",
                PhoneNumber = {
                    new Korisnik.Types.Phone { Broj = "064123456" },
                    new Korisnik.Types.Phone { Broj = "011987654" }
                }
            });

            Console.WriteLine("Dodat je korsinik: {0}", reply.GetType());
            Console.ReadKey();


            var korisnik = await client.ReturnKorisnikAsync(new IdKorisnik { Id = 1 });
            Console.WriteLine($"Vrati korisnik: {korisnik.Name}, {korisnik.Adresa}");
            Console.ReadKey();

            var obrisan = await client.RemoveFromListAsync(new IdKorisnik { Id = 1 });
            Console.WriteLine($"Obrisan je korsinik:  { obrisan}");

            i++;
            goto pocetak;
        }
    }
}
