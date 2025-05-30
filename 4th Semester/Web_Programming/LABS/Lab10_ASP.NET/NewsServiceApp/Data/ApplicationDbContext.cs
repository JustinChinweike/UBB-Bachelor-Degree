using Microsoft.EntityFrameworkCore;
using NewsServiceApp.Models;

namespace NewsServiceApp.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options) { }

        public DbSet<User> Users => Set<User>();
        public DbSet<NewsItem> News => Set<NewsItem>();
    }
}
