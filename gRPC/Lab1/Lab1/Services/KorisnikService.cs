using Grpc.Core;
using Lab1;

namespace Lab1.Services

{
    public class KorisnikServiceImpl : KorisnikService.KorisnikServiceBase
    {
        private readonly ILogger<KorisnikServiceImpl> _logger;
        public KorisnikServiceImpl(ILogger<KorisnikServiceImpl> logger)
        {
            _logger = logger;
        }

        private static Dictionary<int, Korisnik> korisnici = new Dictionary<int, Korisnik>();

        public override Task<Korisnik> AddKorisnik(Korisnik request, ServerCallContext context)
        {
            korisnici.Add(request.Id, request);

            return Task.FromResult(request);
        }

        public override Task<Korisnik> ReturnKorisnik(IdKorisnik req, ServerCallContext context)
        {
            if (!korisnici.ContainsKey(req.Id))
            {
                throw new RpcException(new Status(StatusCode.NotFound, $"Korisnik with ID={req.Id} is not found."));
            }

            if (korisnici.TryGetValue(req.Id, out Korisnik? korisnik) && korisnik != null)
            {
                return Task.FromResult(korisnik);
            }

            throw new RpcException(new Status(StatusCode.NotFound, $"Korisnik with ID={req.Id} is not found."));
        }

        public override Task<IdKorisnik> RemoveFromList(IdKorisnik req, ServerCallContext context)
        {
            Console.WriteLine(korisnici.ToArray().Length);
            if (!korisnici.ContainsKey(req.Id))
            {
                throw new RpcException(new Status(StatusCode.NotFound, $"Korisnik with ID={req.Id} is not found."));
            }
            //korisnici.Remove(req.Id);
            return Task.FromResult(req);
        }
    }
}
