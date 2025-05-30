using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authorization;
using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.Identity;
using NewsServiceApp.Data;
using NewsServiceApp.Models;



var builder = WebApplication.CreateBuilder(args);

//   EF Core – SQL Server
builder.Services.AddDbContext<ApplicationDbContext>(options =>
    options.UseSqlServer(builder.Configuration.GetConnectionString("DefaultConnection")));

//   Cookie authentication
builder.Services.AddAuthentication(CookieAuthenticationDefaults.AuthenticationScheme)
    .AddCookie(options =>
    {
        options.LoginPath = "/Account/Login";
        options.AccessDeniedPath = "/Account/Login";
    });

// Distributed in-memory cache  (required by Session)
builder.Services.AddDistributedMemoryCache();

//  Session (spec asks to create & destroy a session at login/logout)
builder.Services.AddSession();

//   Require auth everywhere by default
builder.Services.AddAuthorization(options =>
{
    options.FallbackPolicy = new AuthorizationPolicyBuilder()
        .RequireAuthenticatedUser()
        .Build();
});

builder.Services.AddControllersWithViews();

var app = builder.Build();


// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();


// AUTOMATIC DB CREATION + SEED USERS
using (var scope = app.Services.CreateScope())
{
    var db = scope.ServiceProvider.GetRequiredService<ApplicationDbContext>();
    db.Database.Migrate();                       // applies migrations (none yet)
    await SeedData.EnsurePopulatedAsync(db);     // inserts admin/guest if needed
}

// ── middleware order ───────────────────────────────────────────────────────────
app.UseStaticFiles();
app.UseRouting();
app.UseSession();            // after routing
app.UseAuthentication();     // cookie auth
app.UseAuthorization();      // role checks

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=News}/{action=Index}/{id?}");


app.Run();










